#include <bits/stdc++.h>
#include <memory>

using namespace std;

struct B
{
    virtual void print() = 0; 
    virtual shared_ptr<B> clone() = 0;
    virtual ~B() {}
};

template <class Derived>
struct BCtrp : B
{
    void print() { cout << "\n B::print"; }    
    shared_ptr<B> doClone()
    {
         return make_shared<Derived>(static_cast<const Derived&>(*this));
    }    

    virtual shared_ptr<B> clone() {
        return doClone();
    }
};

struct D : BCtrp<D>
{

     void print() override { cout << "\n D::print"; }
};


int main()
{
    D b2;
    auto b1 =  b2.clone();    
    b1->print();
    D* d3 = new D;
    shared_ptr<B> b3(d3);
    auto b4 = b3->clone();
    b4->print();
    return 0;
}