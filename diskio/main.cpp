#include <iostream>
#include <thread>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <list>
#include <vector>
#include <future>
#include <sys/mman.h>
#include <sys/stat.h>
#include <atomic>

using namespace std;

void report(int errorId)
{ 
    char errorStr[128];
    cout << errorId << ": " << strerror_r(errorId, errorStr, 128) << "\n";
}


void write_test(int N, int threadN, int perBatch, const std::string& s)
{ 
    list<thread> threads;
    for (int i = 0; i < threadN; i++)
    {
        threads.push_back(thread([N, perBatch, &s](){
            int fd = open("test", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
            if (fd == -1) 
            { 
                int e = errno; report(e); 
                cout << "Failed to open test for appending succsefully!\n"; 
                return -1;
            }

             
            for (int i = 0; i < N; i++)
            {
                string buffer;
                for (int j = 0; j < perBatch; j++)
                    buffer += s;

                ssize_t len = write(fd, (void*)buffer.c_str(), buffer.size());
                if (len == -1) 
                { 
                    int e = errno; report(e); 
                    cout << "Failed to write to a file" << "\n";
                    return -1;
                } 
            }

            return 0;
        }));
    }

    for (auto&& t : threads)
        t.join(); 
}

int test_read(int threadN, int workPerThread)
{
    vector<thread> pool;
    vector<future<bool>> results;
    atomic<int> count{0}; 

    long pageSz = sysconf(_SC_PAGE_SIZE); 
    workPerThread = workPerThread & ~(pageSz - 1);
    //workPerThread = (workPerThread / pageSz) * pageSz;
  //  workPerThread = max<int>(workPerThread, pageSz); 
    cout << "pageSize=" << pageSz << " workPerThread" << workPerThread << "\n";

    for (int i = 0; i < threadN; i++)
    {
       packaged_task<bool()> task([&pool, &results, &count, pageSz, workPerThread](){
           int fd = open("test", O_RDONLY);
           if (fd == -1) 
           { 
               int e = errno; report(e); 
               cout << "Failed to open test for reading succsefully!\n"; 
               return false;
           } 

           struct stat sb;
           if (fstat(fd, &sb) == -1)
           { 
               int e = errno; report(e); 
               cout << "Failed to open test for reading succsefully!\n"; 
               return false;
           }

           auto fileSize = sb.st_size; 
           cout << "fileSize=" << fileSize << "\n";

           int progress = 0; 
           while (progress < fileSize)
           { 
               int prev = count.fetch_add(1, memory_order_relaxed);
               progress = prev * workPerThread; 
               int targetLen = workPerThread; 
               if (targetLen + progress > fileSize) 
                   targetLen = fileSize - progress;

               void* addr = NULL;
               if (targetLen > 0)
               {
                   cout << "progress=" << progress << " targetLen=" << targetLen << "\n"; 
                   addr = mmap(NULL, targetLen, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, progress);
                   if ((void*)-1 == addr)
                   {
                       int e = errno; report(e); 
                       cout << "Failed to mmp file!\n"; 
                       return false;
                   }
               } 

               if (addr != NULL)
               {
                   int r = munmap(addr, targetLen);
                   if (r == -1)
                   {
                       int e = errno; report(e); 
                       cout << "Failed to mmp file!\n"; 
                       return false;
                   } 
               }
           } 

           return true;
         }); 

       future<bool> result = task.get_future();
       results.emplace_back(move(result));
       pool.push_back(thread(move(task)));

    }

    for (int i = 0; i < pool.size(); i++)
    {
        pool[i].join(); 
        try
        {
        if (!results[i].get())
          return -1;
        }
        catch (...)
        { cout << "exception\n"; return -1; }
    }

    return 0; 
}

int main(int argc, char* argv[])
{
    if (argc < 6) 
    {
        cout << "incorrect input arguments!\n";
        return -1;
    }

    int N = atoi(argv[2]);
    int threadN = atoi(argv[3]);
    int perBatch = atoi(argv[4]); 
    int maxLoad = atoi(argv[5]); 
    string s(argv[1]);
    s += '\n';

    if (test_read(threadN, maxLoad / threadN))
       return -1;
//    write_test(N, threadN, perBatch, s);
    return 0;
}
