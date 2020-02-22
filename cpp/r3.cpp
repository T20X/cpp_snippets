#include <bits/stdc++.h>
using namespace std;

struct Data
{
    Data()
    {
    }
    Data(nullptr_t p)
    {}

    int i;
};

template <class T> struct A {};
#include <list>

template <typename T>
struct Alloc
{
  using value_type = T;

  T* allocate(unsigned n);
  void deallocate(T* p, unsigned n);

  Alloc(int) { }

  template<typename U>
    Alloc(const Alloc<U>&) { }
};

template<typename T, typename U>
  bool operator==(Alloc<T>, Alloc<U>) { return true; }
template<typename T, typename U>
  bool operator!=(Alloc<T>, Alloc<U>) { return false; }

constexpr bool b
  = std::is_default_constructible<std::list<bool, Alloc<bool>>>::value;

int main()
{    
    cout << "\nb=" << b << "\n";

    Data n(0);
    vector<unique_ptr<Data>> v;          
    cout << "\ntest";        
    Data d;
    cout << "\n d.i=" << d.i;
    A<struct S1> a;
    return 0;       
}

