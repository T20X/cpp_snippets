#pragma once

#include <boost/type_index.hpp>
#include <cstdint>
#include <iostream>

namespace utils
{

    using namespace std;

    template <typename deleted_type>
    void del(deleted_type*& p)
    {
        if (&p)
        {
            delete p;
            p = nullptr;
        }
    }

    template <typename T>
    std::string typeName()
    {
        return boost::typeindex::type_id_with_cvr<T>().pretty_name();
    }

    template <typename T>
    void print1(const T& arg)
    {
        std::cout << arg << "|";
    }

    template <typename... T>
    void  print(const T&... args)
    {
        std::cout << endl;
        int dummy[] = { 0, ((void)print1(args), 0) ... };
        std::cout << endl;
    }

    void printX()
    {    
    }


    template <typename T>
    void printX(const T& arg)
    {
        print1(arg);
    }

    template <typename F, typename... T>
    void  printX(const F& first, const T&... args)
    {        
        print1(first);
        printX(args...);        
    }

    template <typename... T>
    void printV2(const T&... args)
    {   
        std::cout << endl;
        printX(args...);
        std::cout << endl;
    }

    template <class T>
    std::string printBits(T v)
    {
        std::string r;
        uint64_t sz = sizeof(T) * 8U;
        for (uint64_t i = sz; i >0; --i) 
            r.push_back(((uint64_t)v & ((uint64_t)1U << (i-1U))) ? '1' : '0');
        return r;
    }

}


