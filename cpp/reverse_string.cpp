#include <string>
#include <iostream>
#include <vector>
#include <exception>

using namespace std;
char* reverse(char* s)
{
    if (!s || *s == '\0')
     return s;

    char* begin = s;
    char* end = begin;
    while (*++end != '\0'); 
    
    --end;    
    while (begin < end) 
    {   
        std::swap(*begin, *end);
        ++begin;
        --end;
    }

    return s;
}

void reverse(std::string& s)
{
    if (s.empty()) 
        return;

    auto front = s.begin();
    auto back = s.end();

    while (front < prev(back))
    {
        back--;
        std::iter_swap(front, back);
        front++;        
    }
}

class myexception : public std::exception
{
public:
    myexception(const char* s)
    {
    }
};

class otherexception : public std::exception
{
public:
    otherexception(const char* s)
    {
    }
};

class F
{
void g()
{
    auto f1= [this](auto l, decltype(l) r){
        std::cout << p;
    };
}
int p;
};


void f()
{
    try
    {
        //throw myexception("asd");
       throw std::exception();
    }
    catch (std::exception e)
    {
        throw;
    }

}


void g()
{
    try
    {
        {
            f();
        }
    }    
    catch(const otherexception& e)
    {
        std::cerr << " \n(1)asdas" << e.what() << '\n';
    }
       
    
}


int main()
{
    {
        char s[] = "asdfk";    
        char* r = reverse(s);
        cout << "\n r=" << r;
    }

    {
        char s[] = "a";    
        char* r = reverse(s);
        cout << "\n r=" << r;
    }
    {
        char s[] = "abdc";    
        char* r = reverse(s);
        cout << "\n r=" << r;
    }

    {
        string s("a");
        reverse(s);
        cout << "\n r=" << s;
    }

    {
        string s("aba");
        reverse(s);
        cout << "\n r=" << s;
    }

    {
        string s("abcd");
        reverse(s);
        cout << "\n r=" << s;
    }

g();
    int p(0);
    int k{0};
    p = 12222 + k++;
    std::vector<int>  v2{1,2,3};
    v2.erase(v2.begin(), v2.begin());
    std::cout << "\n " << v2[0] << " " << v2[1] << " " << v2[2];
    std::cout << "\n" << p;
    
}