#include <bits/stdc++.h> 
using namespace std;

struct A
{
    string s1;
    A(const A& o)
    {
        s1 = o.s1;
    }

    template <typename T>
    A(const T& o)
    {
        s1 = o.s1;
    }
};

struct B : A
{
    string s2;
};

int main()
{
    A a1("sadfsad");
    return 0;
}
