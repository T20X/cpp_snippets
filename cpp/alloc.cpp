#include <memory>
#include <iostream>
#include <assert.h>
#include <vector>
#include <list>
#include <unordered_map>
#include <map>
using namespace std;

/*
Just override malloc and free in your own libarary. And by loading these with LD_PRELOAD your malloc and free will be executed rather than the standard one

Array allocation may supply unspecified overhead, which may vary from one call to new to the next. The pointer returned by the new-expression will be offset by that value from the pointer returned by the allocation function. Many implementations use the array overhead to store the number of objects in the array which is used by the delete[] expression to call the correct number of destructors. In addition, if the new-expression is used to allocate an array of char, unsigned char, or std::byte, it may request additional memory from the allocation function if necessary to guarantee correct alignment of objects of all types no larger than the requested array size, if one is later placed into the allocated array.

*/

struct B
{
};

 struct alignas(128) T : public virtual B
{
    int t = 80;
  
    T() { }
    //~T() {}
    //string s;
    virtual ~T() {}
    static void* operator new[]( std::size_t count, void* ptr, bool v)
{
    cout << "\n operator new PTR" << " size=" << count;
    return ptr;
}
    static void* operator new[]( std::size_t count)
{
    cout << "\n operator new" << " size=" << count;
    return ::operator new(count);
}
};

struct D : T
{
    int k;
    double p;
     double p2;
      double p3;
      char d[100];
};



void* operator new[]( std::size_t count, std::align_val_t al)
{
    cout << "\n AUTO ALIGHHMENT GLOBAL operator new" << " size=" << count;
   return ::operator new(count);
}

void* operator new[]( std::size_t count)
{
    cout << "\n GLOBAL2 operator new" << " size=" << count;
   return ::operator new(count);
}

list<class PO> lis;
vector<class PO> vec;

struct PO
{
};

struct Val
{
};
int main()
{


    static constexpr std::align_val_t _al = std::align_val_t(alignof(T));
    //alignas(T) unsigned char buffer[sizeof(T) * 15 + (size_t)_al];
    char* buffer = (char*)::operator new[](sizeof(T) * 15 + (size_t)_al, _al);   
    cout << "\n orig size=" << sizeof(T) * 15 << " alignment size=" << (size_t)_al;
    //T o[15];
    T* a = new ((void*)buffer, true) T[15]{};
    a[14].t=1000000000001;
    //cout << a[14].t;
   // assert(a == &a[0]);   
    cout << "\n end";
    cout << "\n --------------";
    char* buffer2 = (char*)::new T[15];
     cout << "\n --------------";

    T* p = new D[90];
    p[3].t=3;
    cout << "\n" << p->t;
    //++p;
    //++p;
   // ++p;
    cout << "\n" << p->t;
    cout << "\n" << p[0].t;
    cout << "\n" << p[1].t;
    cout << "\n" << p[2].t;
    cout << "\n" << p[3].t;
    cout << "\n" << p[4].t;
    cout << "\n" << p[5].t;
    cout << "\n" << p[6].t;
    cout << "\n" << p[7].t;
    cout << "\n" << p[8].t;
    cout << "\n" << p[9].t;
    cout << "\n" << p[10].t;
    cout << "\n" << p[11].t;
    cout << "\n" << p[12].t;
    cout << "\n" << p[13].t;
    ++p;
    cout << "\n" << p->t;
    return 0;
}