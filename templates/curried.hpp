#pragma once

#include <tuple>
#include <functional>
#include <iostream>

using namespace std;

namespace curried
{
    struct A
    {
        A(int i) {}
        A(A&& o) noexcept
        {
            cout << "\n A::A(&&)";
        }

        auto& operator=(A&& o) noexcept
        {
            cout << "\n A::operator=(A&&)";
            return *this;
        }
    };

    template <typename F, typename... Args>
    struct Curry
    {
    public:
        Curry(F& func, Args... args)
            :_func(func), _args(args...)
        {
        }

        template <typename T>
        class Test;

        template <typename... OtherArgs>
        auto operator()(OtherArgs&&... other)
        {
            auto otherAsTuple = forward_as_tuple(forward<OtherArgs>(other)...);
            //Test<decltype(otherAsTuple)> t1;
            auto& allArgs = tuple_cat(_args, otherAsTuple); 
            //Test<decltype(allArgs)> t2;
            return std::apply(_func, allArgs);
        }


    private: 
        F& _func;
        tuple<Args...> _args;
    };

    int product(int& x0, int x1,int x2,int x3,int& x4, int& x5, int&& x6) 
    {
        x5 = 200;
        x0 = 100;
        return x1 * x2 * x3 * x4;
    }

    static void test()
    {
        int x0, x5=300,x4=2;
//        Curry<decay<decltype(product)>::type, int&, int, int, int> c(product, x0, 2, 2, 2);
 //       cout << "\n " << c(x4, x5, 2) << " x0=" << x0 << " x5=" << x5;
    }
}
