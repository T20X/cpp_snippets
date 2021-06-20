#include <algorithm>
#include <iostream>
#include <cmath>
#include <memory>

#include <pmmintrin.h>

using float_simd = __m128;
using double_simd = __m128d;
using int_t = int;

//float_simd sqrt(float_simd a) { return _mm_sqrt_ps(a); }
//double_simd sqrt(double_simd a) { return _mm_sqrt_pd(a); }

namespace test 
{
    struct Value {};
    template <class T>
    void f(const T& v)
    {
        std::cout << "test::f()" << std::endl;
    }

    void f(const Value& v)
    {
        std::cout << "test::override::f()" << std::endl;
    }
}

namespace test2
{
    struct Value {};
    template <class T>
    void f(const T& v)
    {
        std::cout << "test2::f()" << std::endl;
    }

    void f(const Value& v)
    {
        std::cout << "test2::override::f()" << std::endl;
    }
}

struct Value2
{
};
int sqrt(const Value2& )
{
    std::cout << "global::sqrt()" << std::endl;
    return 0;
}
int sqrt(const float_simd& )
{
    std::cout << "global:float_simd::sqrt()" << std::endl;
    return 0;
}
template <class T>
void callFthroughtempalte(const T& v)
{
    f(v);
}

template <typename T>
void do_fancy(T val) 
{
    using std::sqrt;
    auto ret = sqrt(val);
    (void)ret;
}

template <class T>
void p(T v)
{
    using std::sqrt;
    auto ret = sqrt(v);
    (void)ret;
}

int main()
{
    callFthroughtempalte(test2::Value{});
    using test::f;
    p(Value2{});
    p(100.1);
    do_fancy(Value2{});
    do_fancy(int_t{});
    do_fancy(float_simd{});
    //f(Value2{});
    return 0;
}