#include <bits/stdc++.h>
#include "header_test.h"
using namespace std;

template <typename T>
struct Alloc  
{
  using value_type = T;

  T* allocate(unsigned n);
  void deallocate(T* p, unsigned n);

  Alloc() {}
  Alloc(int) noexcept { }
  Alloc(Alloc&&) {}
  Alloc& operator=(const Alloc<T>& other);

  template<typename U>
    Alloc(const Alloc<U>&) noexcept { }
};

template<typename T, typename U>
  bool operator==(Alloc<T>, Alloc<U>) { return true; }
template<typename T, typename U>
  bool operator!=(Alloc<T>, Alloc<U>) { return false; }

constexpr bool b
  = std::is_nothrow_default_constructible<std::list<bool, Alloc<bool>>>::value;

constexpr bool b2
  = true;//std::is_default_constructible<Alloc<bool>>::value;

constexpr bool b3 = true;//std::is_nothrow_default_constructible<Alloc<bool>>::value;

constexpr int f(double d)
{
    double e = d * 2.51;
    const int x = 1;
    return e;
}

template <typename T, size_t N>
constexpr size_t array_size(T (&a)[N])
{
    return N;
}

int main()
{
    static_assert(!std::is_nothrow_move_constructible<list<int, Alloc<int>>>::value, "MyType should be noexcept MoveConstructible");
    static_assert(!std::is_nothrow_default_constructible<list<int, Alloc<int>>>::value, "MyType should be noexcept MoveConstructible");
    //std::list<bool, Alloc<bool>> l;
    cout << "\nb1= " << b << "b2=" << b2 << " : " << b3 << "\n";
    //Alloc<int> t;
    //Alloc<int> t2 = t;
    list<int> l1;
    list<int> l2;
    
    //l1.push_back('1');
    if (l1 == l2) cout << "equal";

    constexpr double d1 = 6.6;
    constexpr double d0 = 111111.11;
    constexpr int d2 = d0;
    int arr[f(d1)];
    static_assert(array_size(arr) == f(d1), "asdas");
    cout << "\narray size = " << array_size(arr) << "is_literal_type=" << is_literal_type<double>::value;
    int x1 = f(12.4);

 //   test();
    bool f = true;
    f &= (1==1);
    f &= (1!=1);
    std::cout << "\nF=" << f;
    return 0;
}
