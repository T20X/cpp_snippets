#include "C.hpp"

#include <iostream>
inline int foo()
{ 
 return 0;
}

inline int eoo()
{
    return 10000;
}


void boo3()
{
     int (*ptrFun)()  = &eoo;
     ptrFun();
    std::cout << "\n" << eoo() << " - " << reinterpret_cast<uint64_t>(&foo) << " - " << ptrFun();
    too();
    foo();
}

