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
    


std::mutex mtx;
std::condition_variable cv;

int turn = 0;
int index = 0;

void worker(int tid, const std::string& s, int chunk, int nthreads)
{
    int n = s.size();
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);

        // block until it's my turn
        cv.wait(lock, [&] { return turn == tid; });

        std::cout << "Thread" << tid + 1 << ": ";
        for (int i = 0; i < chunk; ++i)
        {
            std::cout << s[index % n];
            ++index;
        }
        std::cout << "\n";

        // move turn
        turn = (tid + 1) % nthreads;

        lock.unlock();
        cv.notify_all(); // cv.notify_one()
    }
}

int main()
{
    std::string s = "ABCDEFGHIJ";
    int chunk = 3;
    int nthreads = 4;

    std::vector<std::thread> threads;
    for (int i = 0; i < nthreads; ++i)
        threads.emplace_back(worker, i, std::cref(s), chunk, nthreads);

    for (auto& t : threads) t.join();

    return 0;
}

