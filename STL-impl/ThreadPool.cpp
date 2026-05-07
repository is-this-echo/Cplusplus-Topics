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

 
class ThreadPool
{
public:
    ThreadPool(int threadCount = 0)
    {
        for (int i = 0; i < threadCouunt; ++i)
            workers.emplace_back([this](){ executeTask(); });
    }

    template <class F, class... Args>
    void enqueue(F&& func, Args ...args)
    {
        auto task = std::bind(F, ...args);

        std::unique_lock<std::mutex> lck(mtx_);
        q.emplace(task);
        lck.unlock();

        cv_.notify_one();
    }

    ~ThreadPool()
    {
        cv_.notify_all();

        for (auto& thread : workers)
            thread.join();
    }

private:

    void executeTask()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lck(mtx_);
            cv_.wait(lck, [this]() { return tasks_.size() > 0; });

            auto task = q.front();
            q.pop();

            lck.unlock();
            task();
        }
    }

    std::mutex mtx_;
    std::condition_variable cv_;
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
};

    
int main()
{
    fastio();
    
    return 0;
}