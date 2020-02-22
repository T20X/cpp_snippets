#include <memory>
#include <iostream>
using namespace std;

struct A
{
    using Ptr = shared_ptr<A>;
    A() { cout << "\n A::A()"; }
    ~A() { cout << "\n A::~A()"; }
    int i = 0;
};

struct Holder
{
    Holder(A::Ptr& a):a_(a) {}
    A::Ptr& a_;
};

int main()
{
    shared_ptr<A> p(new A);    
    Holder h(p);
    std::cout << "\n" << (h.a_ ? " fresh " : "done");  
    p.reset();
    std::cout << "\n" << (h.a_ ? " fresh " : "done");  
    return 0;
}