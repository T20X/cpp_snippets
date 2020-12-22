#include <bits/stdc++.h>
#include <array>

using namespace std;

template <class T>
struct Base
{
    struct Node
    {
        int i = 0;
    };
};

template <class T>
struct D : public Base<T>
{
    using typename Base<T>::Node;
    array<Node,10> n;
};

int main()
{
    D<int> d1;
    std::cout << std::numeric_limits<long>::max();
    std::cout << "\n" << std::numeric_limits<long long>::max();
    std::cout << "\n" << std::numeric_limits<int>::max();
    return 0;
}