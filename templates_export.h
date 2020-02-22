#pragma once
#include <iostream>

struct Boo
{
};

template <typename T>
struct Foo
{
    Foo() {
        std::cout << "\n Foo::Foo()";
    }
    Foo(const Foo& o) = delete;
    Foo& operator=(const Foo& o) = delete;
    template <typename O> Foo(const Foo<O>& o) {
        std::cout << "\nFoo::Foo(cosnt O&) called";
    }
    template <typename O> Foo& operator=(const Foo<O>& o)  {
        std::cout << "\nFoo::operator=(cosnt O&) called";
        return *this;
    }
};