#include <string>
#include <iostream>
#include <optional>
#include <vector>
using namespace std;


struct MyType
{
    MyType() { cout << "\n MyType::MyType()"; }
	MyType(int) {}
//	MyType(const optional<MyType>& other) {}
	MyType(const optional<int>& other) { cout << "\n optional="; }
    ~MyType()
    {
        std::cout << "\n MyType::~MyType";
    }
    std::string s_;
};

union Otro
{
    string s_;
};

union Storage
{
    Storage():t_()
    {
        cout << "\n Storage::Storage()";
    }
    Storage(const MyType& l):t_(l){}
    Storage(initializer_list<MyType> l){}
    ~Storage() 
    {
        cout << "\n Storage::~Storage()";
  //      t_.~MyType();
    }
    MyType t_;
};

struct T
{
    int dl;
    int d;
};


int main()
{

    optional<MyType> o{MyType()};
    optional<MyType> o1{2};
    optional<MyType> o2(2);
    MyType t1;
    optional<MyType> t2;
    optional<MyType> o3(2);
    cout << "\n -------------";
    optional<MyType> o4(t2);

    cout << "\n-------asdfasdf-----------";
    optional<MyType> st3 ( optional<int>(2) );
    cout << "\n-------asdfasdf-----------";

    {
        Storage st;
        st.t_ = MyType();
        cout << "\n end";
        Storage st2{MyType()};
        Storage st3{MyType()};
    cout << "\n-------optinoal-----------";
        Storage st4{optional<int>()};
    }
    cout << "\n------------------";
    {
        Storage st4 = MyType();
    } 

}
