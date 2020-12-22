//#include <bits/stdc++.h>
#include <iostream>
#include <boost/type_index.hpp>
#include <utils.h>

using namespace std;
using namespace boost; 


int main()
{
    auto f = [](auto p) {
        cout << "\n " << utils::typeName<decltype(p)>();
    };
    int l;
    f(std::ref(l));
    return 0; 
}

