#include <iostream>
#include "Variable.h"
#include "C.hpp"
extern int foo();
extern int too();
extern void boo3();
extern int eoo();
int main()
{
    //int *p = new int[1000000];
    //:w
    //std::cout << "\n r=" << foo();
    std::cout << foo();
    //std::cout << "\n" << too();
    std::cout << "\n" << Kath::hi;
    std::cout << "\n" << g::hi_global;
     int (*ptrFun)()  = &eoo;
    std::cout << "\n" << eoo() << " - " << reinterpret_cast<uint64_t>(&foo) << " - " << ptrFun();
    //std::cout << "\n " << eoo();
    boo3();
    
//    getchar();
    return 0;
}

