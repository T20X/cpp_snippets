#include <iostream>
#include <vector>
using namespace std;

class Base
{
public:
    Base() = default;
    explicit Base(int p) {}
    Base(const Base& other)
    {
        cout << "\n" << " Base::Base";
    }

};

class Base2
{
    public:
        operator Base(){ return Base(); }
};

class D : public Base
{
public:
    using Base::Base;
    D(const D& o) = default;

};


int main()
{
    D d1;
    D d2=d1;
   Base b = Base2(); 
    return 0;
}
