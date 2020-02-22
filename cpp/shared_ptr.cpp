#include <iostream>
#include <type_traits>
#include <algorithm>

template <typename T>
class shared_ptr
{
private:
    struct ControlBlock
    {
        size_t _refCount{1};   
    };

    ControlBlock* _cb{nullptr};
    T* _alias{nullptr};

public:
    constexpr shared_ptr() noexcept = default ;       
    template <typename Y/*, typename = std::enable_if_t<std::is_convertible_v<Y*, T*>>*/>
    explicit shared_ptr(Y* data)
    {
        bootstrap(data);
    }

    constexpr explicit shared_ptr(std::nullptr_t) noexcept
    {       
    }

    ~shared_ptr()
    {        
        release();
    }

    shared_ptr(const shared_ptr& other) noexcept      
    {
        copyConstruct(other);
    }
    
    template <typename Y>
    shared_ptr(const shared_ptr<Y>& other) noexcept        
    {       
        copyConstruct(other);
    }

    shared_ptr(shared_ptr&& other) noexcept      
    {    
         moveConstruct(std::move(other));  
    }

    template <typename Y>
    shared_ptr(shared_ptr<Y>&& other) noexcept
    {       
        moveConstruct(std::move(other));
    }

    shared_ptr& operator= (const shared_ptr& other) noexcept
    {
        shared_ptr(other).swap(*this);
        return *this;
    }

    template <typename Y>
    shared_ptr& operator=(const shared_ptr<Y>& other) noexcept
    {
        shared_ptr<Y>(other).swap(*this);
        return *this;
    }

    template <typename Y>
    shared_ptr& operator=(shared_ptr<Y>&& other) noexcept
    {
        shared_ptr<Y>(std::move(other)).swap(*this);
        return *this;
    }  

    size_t count() const
    {
        return _cb ? _cb->_refCount : 0;
    }

    T* operator->() const
    {
        return _alias;
    }
    
    const T& operator*() const
    {
        return *_alias;
    }

    T& operator*() //undefined is no data!
    {
        return *_alias;
    }

    operator bool() 
    {
        return _alias;
    }

private:
    void release()
    {        
        if (_cb)
        {
            if (!--_cb->_refCount)
            {
                if (_alias) delete _alias;                                 
                //_alias = nullptr;
                delete _cb;   
            }
        }
    }

    template <typename Y>
    void bootstrap(Y* data)
    { 
        try
        {   
            _cb = new ControlBlock{};      
            _alias = data;     
        }
        catch (const std::exception&)
        {
            delete data;
            throw;
        }
    }

    template <typename Y/*, typename = std::enable_if_t<std::is_convertible_v<Y*, T*>>*/>
    void copyConstruct(const shared_ptr<Y>& other)

    {
        _cb = other._cb;
        _alias = other._alias;
        if (_cb) ++_cb->_refCount;
    }

    template <typename Y/*, typename = std::enable_if_t<std::is_convertible_v<Y*, T*>>*/>
    void moveConstruct(shared_ptr<Y>&& other)
    {
        _cb = other._cb;
        _alias = other._alias;

        other._cb = nullptr;
        other._alias = nullptr;        
    }

    template <typename Y/*, typename = std::enable_if_t<std::is_convertible_v<Y*, T*>>*/>
    void swap(shared_ptr<Y>& other)
    {     
        std::swap(other._cb, _cb);
        std::swap(other._alias, _alias);
    }    

    void clear(shared_ptr& other)
    {
        other._cb = nullptr;
        other._alias = nullptr;
    }
};


using namespace std;
int main()
{
    struct S
    {
        S() { cout << "S::S()\n"; }
        virtual void f() { }
        virtual ~S() { cout << "S::~S()\n"; }
    };

    struct A
    {
            int a;
            int b;
            int c;
            A() {}
            
    };

    struct D : public S, public A
    {
         virtual void f() { }
        D() { cout << "D::D()\n"; }
        virtual ~D() { cout << "D::~D()\n"; }
    };

    shared_ptr<S> p(new S);
    shared_ptr<S> p1(p);
    {
        shared_ptr<S> p2 = p;
        shared_ptr<S> p3;    
        p3 = p;
    }
    shared_ptr<S> p4(new S);
    shared_ptr<S> p5;
    p4 = p5;
    cout << "---\n";
    shared_ptr<S> p6(new S);
    shared_ptr<S> p7(std::move(p6));
    shared_ptr<S> p8;
    p8 = std::move(p7);

    cout << "---\n";
    {      
        shared_ptr<S> p10(new S);  
        p10 = std::move(shared_ptr<S>{});
    }
    cout << "---\n";
    shared_ptr<S> p12(new S);
    p12 = p12;
    p12 = std::move(p12);
    p12 = shared_ptr<S>(nullptr);
   // cout << "\np12 count = " << p12.count();
   // S* source = p12.operator->();
   // S sourceCop = *p4;
    cout << "\np4 count = " << p5.count();
    cout << "---\n";

    shared_ptr<S> x(new D);
    shared_ptr<S> x1;
    x1 = x;

    cout << "\n common";
    return 0;
}