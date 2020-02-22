#include <iostream>
#include <assert.h>
using namespace std;
class A
{
public:
    virtual ~A() = default;
    virtual void f1() {}
    virtual void f2() {}
    virtual void f12() {} 
    int t1 = 0;
    int t2 = 0;
    int t3 = 0;
    int t4 = 0;
    int t5 = 0;
    double a;
    double k;
    double k9;
    double k91;
    int t6 = 0;
    int t7 = 0;
};

class B
{
public:
    int o;
    int p;
    int p1;
    int p3;
    int p31;
    int p4;
    int p41;
    //virtual ~B() = default;
    virtual void f3() {}
    virtual void f4() {}
    virtual void f5()
    {
        cout << "\n this BBB=" << this;
    }
    int t = 0;
    int b = 1;
    int b1 = 1;
    int b2 = 1;
    int b3 = 1;
    int b4 = 1;
    int b5 = 1;
};

class C : public A, public B
{
public:
  //  virtual ~C() = default;
    virtual void f3() {}
    virtual void f1() { cout << "\n YESSSSSSSSS"; }
    virtual void f6() {}
    void test()
    {
        cout << "\n ptr=" << this;
    }
    int i = 0;
    int p = 0;
    int p1 = 0;
};

class K 
{
    public:
        virtual void f20() {}
        virtual void f21() {}
};

class D : public C, public K
{
  public:
      virtual void f4() {}
      virtual void f20() {}
};

struct T
{
      virtual void f22() {}
};

class Y : public T, public C
{
  public:
      virtual void f41() {}
      virtual void f201() {}
};



int main()
{
    C* c = new C{};

    uint64_t* _this = (uint64_t*)c;
    cout << "\n _this " << _this;
    uint64_t* vtablePtr = (uint64_t*)(*_this);
    cout << "\n vtable=" << vtablePtr;
    void (*func)(uint64_t* th) = (void (*)(uint64_t* th))vtablePtr[2];
    func(_this);
 ///   (vtablePtr[1]();
//        cout << "\n c ptr=" << c << " vptr=" << ((void*)c)[0];
    c->test();
        B* b = c;
    void* d = dynamic_cast<void*>(b);
    assert(d==(void*)c);

    B* a = c;
    a->f3();
    a->f5();
    //A* a2  = dynamic_cast<A*>(a);
    return 0;

}

