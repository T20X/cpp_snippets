#include <new>
#include <memory>
#include <iostream>
using namespace std;

struct A
{
    int a;
};

int main()
{
    const shared_ptr<A> p{new A};
    p->a=1;
    p->a=100;
    cout << "\n p->a" << p->a;

    return 0;
}