#include <iostream>
#include <type_traits>
#include <array>


template <typename C, size_t N, typename std::enable_if_t<std::is_same_v<C,const char>,int> = 1>
void f2(C (& str)[N] )
{
    //std::cout << "\n log2:" << str;
}


void f(const char* str)
{
     const char s2[] = "asdf";
    //std::cout << "\n log: " << str;
    std::cout << "\n address" << &s2;
}

int main()
{
    char* p = "asdasd";
    f(p);
    f("asdfs");
 

    f2("asdfs");

    char s1[] = "asdf";
    f2("asdfs");

    const char s2[] = "asdf";
    f2(s2);

    const char s3[] = "asdf";
    f2(s3);
    std::array<int,10> a1;
      f("asdfasd");
      std::array<int,10> a2;
      std::array<int,10> a3;
      f("sadf");

    const char* s4 = "asdf";
    //f2(s4);

    //f2(s1);
   // f2(p);
    return 0;
}