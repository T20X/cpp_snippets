#include <string>
#include <iostream>
#include <tuple>
using namespace std;

namespace _private
{
    template <typename T>
    struct _my_add_pointer
    {
        using type = typename remove_reference<T>::type*;
    };

    /*template <typename T>
    struct _my_add_pointer<T, 
    {
        using type = T*;
    };*/
}


template <typename T>
struct my_add_pointer
{
    using type = typename _private::_my_add_pointer<T>::type;
};


/*template <typename T>
struct my_add_pointer<T&>
{
    using type = T*;
};

template <typename T>
struct my_add_pointer<T&&>
{
    using type = T*;
};*/


template < 
  template < class...> class A, 
    class B 
    //class... T
   >
struct r1ename
{

};

template <template < class...> class A,   class B>
struct test1;
using test1_short = test1<std::tuple, std::tuple<int,int,int>>;



template<  template < class...> class A
        ,  template < class...> class B
        , class... Elements
        > 
struct r1ename<A, B<Elements...>>
{
  using type = A<Elements...>;
};

template <class...>
 struct mylist;

using my_variant = r1ename<mylist , std::tuple<int,short>>;

template <typename T>
using my_add_pointer_t = typename my_add_pointer<T>::type;

int main()
{
    {
        my_add_pointer_t<int> p;
        static_assert(is_same<int*, decltype(p)>::value, "failed #1");
    }

    {
        my_add_pointer_t<const int> p;
        static_assert(is_same<const int*, decltype(p)>::value, "failed #1");
    }

    {my_add_pointer_t<void> p;
     static_assert(is_same<void*, decltype(p)>::value, "failed #1");}

    {my_add_pointer_t<int&> p;
     static_assert(is_same<int*, decltype(p)>::value, "failed #1");}

    {my_add_pointer_t<int&&> p;
     static_assert(is_same<int*, decltype(p)>::value, "failed #2");}    

    {
        my_add_pointer_t<const int&> p;
        static_assert(is_same<const int*, decltype(p)>::value, "failed #2");
    }    

    {
        my_add_pointer_t<int&> p;
        static_assert(is_same<int*, decltype(p)>::value, "failed #2");
    }    

    return 0;
}