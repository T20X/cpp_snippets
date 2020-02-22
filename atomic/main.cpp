#include <bits/stdc++.h>
using namespace std;

struct S
{
    int x = 0;
};

S _s { 1 };
struct A
{
    A() { cout << "\nA::A()"; } 
    ~A() { cout << "\nA::~A()"; } 
    A(const A& other) { cout << "\nA::copyu"; }
    A& operator=(const A& other) { cout << "\nA::="; return *this; } 
    string s1;
};

struct A1
{
    A1() { cout << "A1\n::A1()"; } 
    ~A1() { cout << "\nA1::~A1()"; } 
    A1(const A1& other) = delete;
    A1& operator=(const A1& other) = delete;
    A1& operator=(A1&& other) = delete;
    string s1;
};



struct B
{
    A a_;
    B() { cout << "\n::B()"; } 
    ~B() { cout << "\n::~B()"; } 

};

struct B1
{
    A1 a1_;
    A1 f1() { return A1{}; }
};

struct C
{
    bool v;
};


void f(C&& c1)
{
}

int main()
{
    cout << "long sz=" << sizeof(long);
    cout << "long sz=" << sizeof(int);

    switch (std::get_pointer_safety()) {
        case std::pointer_safety::strict:    std::cout << "strict\n"; break;
        case std::pointer_safety::preferred: std::cout << "preferred\n"; break;
        case std::pointer_safety::relaxed:   std::cout << "relaxed\n"; break;
    }

    cout << "\nmax align = " << alignof(std::max_align_t);
//    A&& a1 = A();
 //   A&& a2 = B().a_;
  //  a2.s1 = "asdasaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaajjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj";

 //   const A& a3 = B().a_;
    cout << "\n sizeofC = " << sizeof(C);
	cout << "\n end";

   // C&& c2 = C();
    //f(std::move(c2));

    //cout << "\n str=" << a2.s1;


    cout << "\n new....\n\n\n\n\n\n\n";
//    A1 a11 = B1().f1(); 
    A&& a4 = B().a_;
    cout << "\n str=" << a4.s1.c_str();
	cout << "\n end2";

    return 0;
}
