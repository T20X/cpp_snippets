#include <bits/stdc++.h>
using namespace std;

struct A
{
    void f(int,int) {}
};

template <typename T>
  struct Test;

int main()
{
    using T1 = _Mem_fn_base<decltype(&A::f)>;
    cout << "\n" << T1::_Arity::value; 
     _Mem_fn_traits<decltype(&A::f)>::__maybe_type t2;
    decltype(t2)::first_argument_type t1;
    //decltype(_Mem_fn_base<decltype(&A::f)>::argument_type) t2;
    return 0;
}
