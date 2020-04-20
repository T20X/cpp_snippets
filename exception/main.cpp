#include <bits/stdc++.h>
using namespace std;

struct BE
{
    virtual ~BE() {}
};

struct DE : BE
{
};


void f(BE& b)
{
    throw b;
}

struct A { A(int x) { throw exception(); } };
struct B { A a_; B() try :a_(1) { } catch (const exception& e) { }  };
int main()
{
    std::vector v;
    v.
    DE b;
    try
    {
        f(b);
    }
    catch (DE& e)
    {
        cout << "\n DE e..";
    }
    catch (BE& e)
    {
        cout << "\n BE e..";
    }

    try
     {
         B b1;
     }
    catch (...)
    {
        cout << "\nexceptio ncaught";
    }
    return 0;
}
