#include <bits/stdc++.h>


struct RefCounter 
{
    RefCounter():c_(new int{1}) {}
    ~RefCounter() { if (d()) delete c_; }
    RefCounter(const RefCounter& other)
        :c_(other.c_)
    {
        i();
    }

    RefCounter(RefCounter&& other):c_(other.c_) { other.c(); }
    RefCounter& operator=(const RefCounter& other)
    {
        d();
        c_ = other.c_;
        i();
    }

    RefCounter& operator=(RefCounter&& other)
    {
        d();
        c_ = other.c_;       
        other.c();
    }

    bool solo() const { return c_ && *c_ == 1; }

    void c() { c_ = nullptr; }
    void i() { c_ && ++(*c_); }
    bool d() { return c_ && !--(*c_); }    

    int* c_ = nullptr;
};

template <class T>
class shared_ptr : protected RefCounter
{
public:    
    shared_ptr() {}
    explicit shared_ptr(T* ptr)
       :ptr_(ptr)
    {
    }

    ~shared_ptr() { release(); }
    shared_ptr(const shared_ptr& other)
        :RefCounter(other),
         ptr_(other.ptr_)
    {
    }

    shared_ptr(shared_ptr&& other)
         :RefCounter(std::move(other)),
          ptr_(other.ptr_)
    {
        other.clear();
    }

    shared_ptr& operator=(const shared_ptr& other)
    {
       if (&other == this)
         return *this;

        release();
        RefCounter::operator=(other);
        ptr_ = other.ptr_;
    }

    shared_ptr& operator=(shared_ptr&& other)
    {
        if (&other == this)
         return *this;

        release();
        RefCounter::operator=(std::move(other));        
        ptr_ = other.ptr_;
        other.clear();
    }

    void swap(shared_ptr& other)
    {
        std::swap(other.ptr_, ptr_);
        std::swap<RefCounter>(*this, other);
    }

    void release()
    {
        if (solo()) delete ptr_;
        clear();
    }

    void clear()
    {
         ptr_=nullptr; 
    }

    operator bool() const { return ptr_; }
    int use_count() const { return c_ ? *c_ : 0; }

private:
    T* ptr_ = nullptr;
};

struct My
{
    My()
    {
        std::cout << "\n My::My()";
    }
    ~My()
    {
        std::cout << "\n My::~My()";
    }
};

template <typename T>
//using ptr=std::shared_ptr<T>;
using ptr=shared_ptr<T>;
int main()
{
    ptr<My> p(new My{});
    assert(p);
    assert(p.use_count()==1);
    {
        auto p1=p;
        assert(p.use_count()==2);
        auto p2=p1;
        assert(p.use_count()==3);
        assert(p2.use_count()==3);
        assert(p1.use_count()==3);
    }
    assert(p.use_count()==1);
    ptr<My> p2(new My{});
    std::cout << "\n (0)-----------";
    p=p2;
    std::cout << "\n (0)-----------";
    assert(p.use_count()==2);
    assert(p2.use_count()==2);
    ptr<My> p3(p2);
    assert(p.use_count()==3);
    {
        auto p1=std::move(p2);
        assert(!p2);
        assert(p1.use_count()==3);
        assert(p.use_count()==3);
        std::cout << "\n (2)-----------\n";
    }
    assert(p2.use_count()==0);
    assert(p.use_count()==2);
    assert(p3.use_count()==2);    
    return 0;
}