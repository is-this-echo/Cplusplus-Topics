/* Debjyoti Ghosh*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
using namespace std;

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define ll long long
#define INF 2e18
#define PI 3.1415926535897932384626
#define mod 998244353
#define f first
#define s second 

double eps = 1e-12;

ll gcd(ll a, ll b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
void google(int t) {cout << "Case #" << t << ": ";}



DummyClass createObj()
{
    // NRVO - Named RVO
    auto sampleObj = DummyClass(5);
    return sampleObj;
}

DummyClass createObj2()
{
    // URVO - Unnamed RVO
    return DummyClass(5);
}

int main()
{
    DummyClass dc = createObj();
    DummyClass dc2 = createObj2();

    return 0;
}

namespace custom
{
template <typename T>
class unique_ptr
{
public:
    explicit unique_ptr(T* ptr = nullptr) : ptr_(ptr)
    {
        std::cout << "unique pointer constructed!";
    }

    ~unique_ptr()
    {
        delete ptr_;
        std::cout << "unique pointer destructed!";
    }

    unique_ptr(const unique_ptr& rhs) = delete;
    unique_ptr& operator=(const unique_ptr& rhs) = delete;

    unique_ptr(unique_ptr&& rhs) noexcept : ptr_(rhs.ptr_)
    {
        rhs.ptr_ = nullptr;
        std::cout << "Move constructed invoked!";
    }

    unique_ptr& operator=(unique_ptr&& rhs) noexcept
    {
        if (this != &rhs)
        {
            delete ptr_;

            this->ptr_ = rhs.ptr_;
            rhs.ptr_ = nullptr;
            std::cout << "Move assignment operator invoked!";
        }
        return *this;
    }

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }

    void reset(T* ptr = nullptr)
    {
        delete ptr_;
        ptr_ = ptr;
    }

    T* get() const { return ptr_; }

    explicit operator bool() const { return ptr_ != nullptr; }
 
private:
    T* ptr_;
};


template <typename T>
class shared_ptr
{
public:
    explicit shared_ptr(T* ptr = nullptr) : ptr_(ptr), refCount_(ptr_ ? new int(1) : 0) {}

    shared_ptr(const shared_ptr& rhs) : ptr_(rhs.ptr_), refCount_(rhs.refCount_)
    {
        ++(*refCount_);
    }

private:
    T* ptr_;
    int* refCount_;
};

} // custom namespace

int main()
{
    custom::unique_ptr<std::string> uptr(new std::string{"anbc"});
    std::cout << *uptr;

    custom::unique_ptr<std::string> uptr2{std::move(uptr)};
    // std::cout << *uptr;
    std::cout << *uptr2;

    uptr = std::move(uptr2);
    std::cout << *uptr;

    return 0;
}


