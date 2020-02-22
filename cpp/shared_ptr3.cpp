#include <bits/stdc++.h>

template <class T>
struct Impl
{
    Impl(T* ptr):p_(ptr)
    { 
        try
        {
            if (ptr) c_= new size_t{1}; 
        }
        catch (...)
        {
            delete p_;
            throw;
        }
    }    

    Impl(const Impl& o) { copyImpl(o);  }
    Impl(Impl&& o) { moveImpl(std::move(o)); }
    ~Impl() { release(); }

    Impl& operator=(const Impl& o)
    {
        if (&o == this) 
        return *this;

        release();
        copyImpl(o);
    }

    Impl& operator=(Impl&& o)
    {
        if (&o == this) 
         return *this;
         
        release();
        moveImpl(std::move(o));
    }

    void copyImpl(const Impl& o)
    {
        c_ = o.c_;
        p_ = o.p_;
        if (c_) ++(*c_);
    }

    void moveImpl(Impl&& o)
    {
        c_ = o.c_;
        p_ = o.p_;
        o.reset();
    }

    void release()
    {
        if (c_ && !--(*c_))
        {
            delete c_;
            delete p_;
            reset();
        }
    }

    void reset()
    {
        c_ = nullptr;
        p_ = nullptr;
    }

    size_t* c_ = nullptr;
    T* p_ = nullptr;
};

template <class T>
class shared_ptr : private Impl<T>
{
public:
    shared_ptr() {}
    explicit shared_ptr(T* ptr=nullptr)
      :Impl<T>(ptr)
    {
    }

    ~shared_ptr() = default;
    shared_ptr(const shared_ptr&) = default;
    shared_ptr(shared_ptr&&) = default;

    shared_ptr& operator=(const shared_ptr&) = default;
    shared_ptr& operator=(shared_ptr&&) = default;

    size_t use_count() const { return this->c_ ? *this->c_ : 0; }
    operator bool() const { return this->p_; }
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