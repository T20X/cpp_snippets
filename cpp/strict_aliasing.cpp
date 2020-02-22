#include <iostream>
#include <cstring>
#include <new>

void foo1( double &si, unsigned int &ui ) {
    si = 8;
    ui = 2.0;

   // return si ;
}

struct foo { int x ; };

struct bar : public foo {};

int foobar( foo &f, bar &b ) {
  f.x = 1;
  b.x = 2;

  return f.x;
}

struct S
{
  const int p;
  S():p(2){}
  S(int v):p(v) {}
  S& operator=(const S& o) 
  {
      memcpy(std::launder(const_cast<int*>(&p)), &o.p, sizeof o.p);
  }
};

void punCharArray()
{
  alignas(sizeof(int)) char data[sizeof(int)];
  int32_t* i = new (data) int{12};  
  std::cout << "\n n=" << *i;
  std::cout << "\n n=" << *reinterpret_cast<int32_t*>(data);
}

int main()
{
    double i = 0;
    foo1(i, reinterpret_cast<unsigned int&>(i));
    std::cout << i ;

    bar b;
    std::cout << "\n foobar=" << foobar(b, b);

    S s1(1);
    s1 = S(2);
    std::cout << "\n p=" << s1.p;

    std::uintptr_t p;
    double d[] {1.1, 1.2, 1.5};
    std::cout << "\n sizeofd=" << sizeof d;

    foo* f1 = new foo;
    foo* const f2 = f1;
    (*f2).x = 1;

    punCharArray();
}

