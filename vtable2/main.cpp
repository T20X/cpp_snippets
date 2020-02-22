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
    //virtual ~B() = default;
    virtual void f3() {}
    virtual void f4() {}
    virtual void f5()
    {
    }
};

class C : public A, public B
{
public:
  //  virtual ~C() = default;
    virtual void f3() {}
    virtual void f1() { }
    virtual void f6() {}
    void test()
    {
    }
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

int main()
{
    C* c = new C{};

 ///   (vtablePtr[1]();
//        cout << "\n c ptr=" << c << " vptr=" << ((void*)c)[0];
    c->test();

    B* b = c;
    void* d = dynamic_cast<void*>(b);

    B* a = c;
    a->f3();
    a->f5();
    //A* a2  = dynamic_cast<A*>(a);
    return 0;

}

