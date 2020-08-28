#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <list>
#include <vector>
#include <string>
#include <stdlib.h>

#include "Utils.hpp"

int main(int argc, char* argv[])
{
    if (argc < 3) return -1;
    


    
    try
    {
        int fd = open("tmp/data", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
        if (fd == -1) utils::report();

        int N = atoi(argv[1]);
        int range = atoi(argv[2]);
        for (int i = 0; i < N; ++i)
        {
            int num = rand() % range;
            std::string buffer;
            if (num == 0)
            buffer = "ttttttttttttttttttttttttttttttttttt\n";
            else
            {

                //buffer += 't';
                for (int j = 0; j < num; j++)
                    buffer += 's';

                //buffer += "arrrtP";
                buffer += '\n';
            }

            int ret = write(fd, (void*)buffer.data(), buffer.size());
            if (ret != buffer.size())
            {
                if (ret == -1) utils::report();
                std::cout << "\npartial write!";
                close(fd);
                return -1;
            }

        }
    }
    catch (const std::exception& e)
    {
        std::cout << "got exception -> [" << e.what() << "]\n";
    }

    return 0;
}