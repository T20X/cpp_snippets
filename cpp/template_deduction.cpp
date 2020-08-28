#include <iostream>
#include <vector>
#include <tuple>
//#include <boost/type_index.hpp>

template <template <typename> class C, typename T>
decltype(auto) get(const C<T>& v, auto index)
{
    std::cout << "\n asdf";
    return v[index];
}

template <class C>
decltype(auto) get2(C&& v, auto index)
{
    return v[index];
}

template <class C>
decltype(auto) get3(C&& v, auto index)
{ 
    return std::forward<C>(v)[index];
}

template <class T>
void f(T&& v)
{    
}
template <template <typename> class Container, typename T>
std::ostream& operator<<(std::ostream& out, const Container<T>& c) {
    bool first = true;
    for (auto x : c) {
        if (!first) out << ", ";
        first = false;
        out << x;
    }
    return out;
}

struct Informer
{
};


template <class = void> struct Temp { static Informer other; };
template <> inline Informer Temp<>::other{};
static auto& g_str2 = Temp<>::other;

int main()
{
    f(20);
    std::vector<int> v{1,2,2};

    std::vector<std::pair<std::string, std::string>> vs;
    //vs.emplace_back(std::make_pair(std::string(10, 'c'), std::string(10, 'c')));
    vs.emplace_back(std::piecewise_construct, 
                    std::forward_as_tuple("dsfsdfsdfsdfsdfsdfsdfsdfsdfsdf"), 
                    std::forward_as_tuple(10, 'c'));
   // std::cout << "\n vs[0]=" << vs[0].first << " -- " <<
           //                     vs[0].second;

    std::cout << "\n " << (-1 % 3U);
    return 0;
}