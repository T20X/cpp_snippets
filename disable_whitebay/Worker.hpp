#pragma once

#include <sys/mman.h>
#include <iostream>
#include <chrono>

#include "Context.hpp"
#include "Utils.hpp"

class Worker
{
public:
    Worker(Context& ctx, int writeBatch)
        :_ctx(ctx), _writeBatch(writeBatch)
    {}    

    struct Interval { int front; int back; };
    using Result = std::unordered_map<int, std::vector<Interval>>;

    void consume(int fd, int sz, int offset, char c)
    {
        char* arena = NULL;
        arena = (char*)mmap(NULL, sz, PROT_READ, MAP_PRIVATE /*| MAP_POPULATE*/, fd, offset);
        if ((void*)-1 == arena)                
            utils::report(); 

        persist(arena, sort(arena, sz, c));
        if (arena != NULL)
        {
            int r = munmap(arena, sz);
            if (r == -1)
                utils::report(); 
        }
    }

private:
    Result sort(char* arena, int sz, char c)
    {
        Result r/*RVO*/;
        int front = 0;
        int back = 0;
        int counter = 0;
        for (int i = 0; i < sz; i++)            
        {
            if (arena[i] == c)
                counter++;
            if (arena[i] == '\n')
            {
                back = i;
                //std::cout << "\ncounter=" << counter << " front=" << front << " back=" << back;
                r[counter].emplace_back(Interval{front,back});
                front = back = i + 1; // step over end of line!
                counter = 0;
            }
        }     
        return r;
    }

    void persist(char* arena, const Result& data)
    {
       //  using namespace std::chrono;
       // auto start = system_clock::now();

        for_each(data.begin(), data.end(), [this, arena, &data](const auto& item)
        {
            int freq = item.first; // Number of target character occurences
            int fd = -1;

            auto lookupIdForWrite = [this](int freq) {
                int fd = -1;
                auto it = _ctx.filesForWrite.find(freq);
                if (it != _ctx.filesForWrite.end())            
                    fd = it->second.first;
                return fd;
            };

            {
                std::shared_lock readLock(_ctx.guard);
                fd = lookupIdForWrite(freq);                
            }
            if (fd == -1)            
            {                                   
                std::unique_lock writeLock(_ctx.guard);                                
                {
                    fd = lookupIdForWrite(freq);                
                    if (fd == -1)
                    {
                        std::string fileName("tmp/tmp2_" + std::to_string(freq));
                        fd = open(fileName.c_str(),
                            O_RDWR | O_EXCL | O_CREAT | O_APPEND, 
                            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

                        if (fd == -1) 
                          utils::report();

                        _ctx.filesForWrite.emplace(freq, std::make_pair(fd, fileName));
                    }
                }
            }

            for (const auto& interval : item.second)    
            {                
                int len = interval.back - interval.front + 1;
                ssize_t done = write(fd, arena + interval.front, len); //appends are atomic since Linux 3.15 kernel!
                if (len != done)
                {
                    if (done == -1) utils::report();
                    throw std::runtime_error("write was not complete!");
                }
            }
        });

       // auto finish = system_clock::now();
       // auto period = finish - start;
    }

    Worker(const Worker&) = delete;
    Worker& operator=(const Worker&) = delete;

private:
   Context& _ctx;
   int _writeBatch;
};
