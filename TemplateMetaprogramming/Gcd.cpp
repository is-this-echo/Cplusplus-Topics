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


// compile time gcd
template <int N, int M>
struct gcd_v
{
    static constexpr int value = gcd_v<M, N % M>::value;
};

template <int N>
struct gcd_v<N,0>
{
    static_assert(N != 0, "GCD undefined for (0,0)");
    static constexpr int value = N;
};

    
int main() {
    fastio();

    static_assert(gcd_v<15,10>::value == 5);
    // static_assert(gcd_v<0,0>::value == 5);
    
    return 0;
}