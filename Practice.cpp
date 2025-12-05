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


template <typename T>
struct PoolAllocator
{
    using value_type = T;

    PoolAllocator() : offset_(0) {}

    T* allocate(size_t blocks)
    {
        int sizeReq = blocks * sizeof(T);

        if (offset_ + sizeReq > sizeof(mempool_))
            throw std::bad_alloc();
        
        T* ptr= reinterpret_cast<T*>(mempool_ + sizeReq);
        offset_ += sizeReq;

        return ptr;
    }

    void deallocate(T* ptr, size_t /* n */)
    {
        // not required as the mempool_ will be freed once it goes out of scope
    }

private:
    char mempool_[50000];
    int offset_;
};


int main()
{
    std::vector<char, PoolAllocator<int>> vec;
    for (auto ch = 'a'; ch <= 'z'; ++ch)
        vec.emplace_back(ch);
    
    for (const auto ch : vec)
        std::cout << ch << " ";

    return 0;
}


