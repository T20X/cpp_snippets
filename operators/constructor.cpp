#include <iostream>
using namespace std;

class Base
{
    public:
    Base(int i){}
    Base(const Base& other) {
    }
};


int main()
{
    Base b1 = Base(10);
    Base b2 = b1;
    Base b3 = 21;
    return 0;
}