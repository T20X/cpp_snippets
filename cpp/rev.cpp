#include <iostream>
#include <string>
#include <string.h>
#include <limits>

using namespace std;

class A;
class Base
{
    int data;
    friend class A;
};

struct D : Base
{
private:
    int data1;
    friend class A;
};


struct A
{
    void f(Base& o)
    {
        o.data=1;
    }
    void f(D& o)
    {
        o.data1=1;
    }
};


string reverse(string str)
{
    auto front = str.begin();
auto back = str.end();

    while (front < back)
    {        
        iter_swap(front++, --back);     
    }

    return std::move(str);
}

char* reverse(char* s)
{
    if (!s) return s;
    size_t len = strlen(s);
    if (!len) return s;

    size_t front = 0, back = len - 1;
    while (front < back) std::swap(s[front++], s[back--]);   
    return s;
}


int main()
{
    string s1("\nabcdefg");
    string orig = s1;
    s1 = reverse(reverse(s1));    
    cout << "\ngood: " << (s1 == orig);

    string s2("ab");
    orig = s2;
    s2 = reverse(reverse(s2));
    cout << "\ngood: " << (s2 == orig);

    string s3("a");
    orig = s3;
    s3 = reverse(reverse(s3));
    cout << "\ngood: " << (s3 == orig);

    char c1[] = "nabcdefg"; cout << "\n" << reverse(c1);
    char c2[] = "n"; cout << "\n" << reverse(c2);
    char c3[] = "np"; cout << "\n" << reverse(c3);
    char c4[] = "npl"; cout << "\n" << reverse(c4);

    cout << "\n m=" << numeric_limits<uint16_t>::max();
    return 0;
}