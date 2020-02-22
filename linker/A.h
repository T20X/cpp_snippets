#pragma once
#include <string>
#include <iostream>
using namespace std;

struct Informer
{
    Informer():s("asdaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") {cout << "\nInformer::ctor at " << reinterpret_cast<int64_t>(this); }
    ~Informer() { cout << "\nInformer::dtor at " << reinterpret_cast<int64_t>(this); }
    const char* c_str() { static const char s[] = "Informer"; return s; }
    int i;
    std::string s;
};

template <class = void> struct Temp { static Informer other; }; 
template <> inline Informer Temp<>::other{}; 


namespace detail
{
inline Informer& str()
{
    //cout << "\nhaha" << __FUNCTION__;
    static Informer str1{};
    return str1;
}
}

static auto& g_str = detail::str();
static auto& g_str2 = Temp<>::other;
inline Informer g_str3{}; //the best!
