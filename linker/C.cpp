#include "A.h"
#include <iostream>

void f()
{
    cout << "\nA::f()";
    int64_t address = reinterpret_cast<int64_t>(g_str.c_str());
    std::cout  << "\nfrom f()=" << g_str.c_str() << ", address=" << address ;
}
