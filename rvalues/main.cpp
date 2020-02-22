#include <iostream>
#include <bits/stdc++.h>
#include <type_traits>
#include <cassert>
using namespace std;

template<typename T>
struct value_category {
    // Or can be an integral or enum value
    static constexpr auto value = "prvalue";
};

template<typename T>
struct value_category<T&> {
    static constexpr auto value = "lvalue";
};

template<typename T>
struct value_category<T&&> {
    static constexpr auto value = "xvalue";
};

// Double parens for ensuring we inspect an expression,
// not an entity


template<class T>
void f_(T&& x, char const *s)
{
    std::cout << s << '\n';
}

template<class T>
void vc(T&& e)
{
    if constexpr (std::is_lvalue_reference<decltype((e))>::value) {
  std::cout << "expression is lvalue\n";
}
else if constexpr (std::is_rvalue_reference<decltype((e))>::value) {
  std::cout << "expression is xvalue\n";
}
else {
  std::cout << "expression is prvalue\n";
}
}

struct A
{
    string s1;
    std::string& f() { return s1; }
    std::string&& f1() { return std::move(std::string("asdas")); }
};

struct X { X(int& o):o_(o) {} int n;int& o_; };

template <class T>
void f2(T v)
{
    decltype(auto) t = forward<T>(v);
    assert((is_same<decltype(t), T&&>::value));
}

int main() 
{
    struct Test
    {
        int k;

    };
    assert((is_trivially_default_constructible<Test>::value));
    assert((is_literal_type<double>::value));
    f2(5);
    A a1;
    f2(a1);
    //auto x3 = auto&& []() { return j; }; // OK: return type is int&
    int j = []<class T>(T t, int i) { return i; }(3, 4);

    int k1;
    int k2;
 if constexpr (std::is_lvalue_reference<decltype((X(k1).o_))>::value) {
  std::cout << "expression is rvalue\n";
    }


    //f(A().f1());
    //f(a1.f());
    return 0;
}
