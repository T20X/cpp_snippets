#include <bits/stdc++.h>
using namespace std;

template <class T>
concept Num = is_integral<T>::value;

int main()
{
    auto f = [](auto n) { 
        return [=](auto other) { return n + other; };
    };
    cout << f(2)(43);
    return 0;
}
