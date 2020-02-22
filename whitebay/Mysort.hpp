#pragma once

#include <thread>
#include <vector>
#include <future>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <algorithm>

#include "Context.hpp"
#include "Worker.hpp"
#include "Utils.hpp"

struct Input
{    
    std::string inputFile;
    std::string outputFile;
    int threadN;
    int maxLoad;
    int writeBatch;
    char c;
};

class MySort
{
public:
    MySort(const Input& params)
        :_params(params)
    {
        auto pageSz = sysconf(_SC_PAGE_SIZE); 
        _workPerThread = (_params.maxLoad / _params.threadN) & ~(pageSz - 1);
        _workPerThread = std::max<int>(_workPerThread, pageSz);
        if (_workPerThread < 1) 
        {
             throw std::runtime_error("workPerThread is less then 1");
        }

        _inFd = open(_params.inputFile.c_str(), O_RDONLY);
        if (_inFd == -1) 
           utils::report();
       
        struct stat sb;
        if (fstat(_inFd, &sb) == -1)
           utils::report();    

        _fileSz = sb.st_size;         
    }

    ~MySort()
    {
        if (_inFd != -1) close(_inFd);
    }

    MySort(const MySort&) = delete;
    MySort& operator= (const MySort&) = delete;

    bool go()
    {
        std::vector<std::thread> pool;
        std::vector<std::future<void>> results;

        for (int i = 0; i < _params.threadN; ++i)
        {
            std::packaged_task<void()> t([this]()
            {
                Worker w(_ctx, 10000);
                int readSoFar = 0; 
                while (readSoFar < _fileSz)
                { 
                    int prev = _ctx.count.fetch_add(1, std::memory_order_relaxed);
                    readSoFar = prev * _workPerThread; 
                    int toReadNow = _workPerThread; 
                    if (toReadNow + readSoFar > _fileSz) 
                        toReadNow = _fileSz - readSoFar;
                        
                    if (toReadNow > 0)
                        w.consume(_inFd, toReadNow, readSoFar, _params.c);
                }
            });

            results.emplace_back(std::move(t.get_future()));
            pool.emplace_back(std::move(t));
        }

        for (auto&& t : pool)     
            t.join();    

        for (auto&& f : results)        
            f.get(); //re-throw exceptions caught in thread functions

        for (const auto& file : _ctx.filesForWrite)    
        {
            auto fd = file.second.first;
            // this will ensure data integrity and for massive amount of data it won't be that big 
            // since by the time of this call kernal would anyway write-back most of data to disk 
            int ret = fsync(fd); 
            if (ret == -1) utils::report();
        }

        return true;
    }



private:
    const Input& _params;    
    Context _ctx;    
    int _inFd{-1};
    int _fileSz{0};
    int _outFd{-1};
    int _workPerThread{0};
};