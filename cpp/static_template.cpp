#include <bits/stdc++.h>
using namespace std;

template <class T>
struct B
{
    static T v;

}; 

struct Item
{
    int v;
    int b;
    Item(int v,int b){}
};


template <typename T>
T B<T>::v = 0; 

template <class T>
auto func() noexcept(noexcept(B<T>::d())) -> decltype(B<T>::d())
{
    cout << "\n HAHAHA";
    return {};
}
void inUni(int&& v)
{
    cout << "\n inUni";
}

void inUni(const int& v)
{
    cout << "\n inUni2";
}


template <typename... T>
void testUnif(T&&... v)
{
    //inUni(v);
    inUni(std::forward<int>(v)...);
}


template <class T>
void func() 
{
    cout << "\n HAHAHA";
    //return {};
}

int main()
{
    vector<Item> v;
    //v.emplace_back({21,4});
    testUnif(1);
    func<int>();
    B<double> v2;
    B<int> v1;
    B<int>::v=1;
    B<double>::v=2.0;
    cout << "B<double>::v=" <<B<double>::v; 
    cout << "B<double>::v=" << B<int>::v;
    return 0;
}