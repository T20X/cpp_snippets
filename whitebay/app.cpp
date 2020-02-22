#include "Mysort.hpp"

int main(int argc, char* argv[])
{
    if (argc < 6)
    {
        std::cerr << "Expect at least 5 params: mysort <input file> <output file> "  
                  << "<threadN> <maxLoadPerThread> <target char>";
        return -1;
    }

    try
    {
        Input params;
        {
            int index = 1;
            params.inputFile.assign(argv[index++]);
            params.outputFile.assign(argv[index++]);
            params.threadN = atoi(argv[index++]);
            params.maxLoad = atoi(argv[index++]);
            params.writeBatch = atoi(argv[index++]);
            params.c = argv[index++][0];            
        }

        using namespace std::chrono;
        auto start = system_clock::now();
        {        
            MySort app(params);
            if (!app.go()) return -1; 
        }
        auto finish = system_clock::now();
        auto period = finish - start;
        std::cout << "\nTotal run time: ["
                  << duration_cast<seconds>(period).count() 
                  << "] sec\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "Caught an exception -> [" << e.what() << "]\n";
        return -1;
    }

    return 0;
}
