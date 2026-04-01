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
    
 

/*
Question - Given a system that has one event and multiple listeners, design and implement a mechanism for the listeners to hear about the event. We want to implement a callback mechanism that allows listeners to register a function that will be invoked when the event fires. The API functions are register_callback() and event_fired().
*/

#include <iostream>
#include <vector>
#include <functional>
#include <mutex>

class EventSystem
{
public:
    using Callback = std::function<void()>;

    void registerCallback(Callback cb)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        callbacks_.push_back(std::move(cb));
    }

    void eventFired()
    {
        std::vector<Callback> local_callbacks;
        // Copy under lock
        {
            std::lock_guard<std::mutex> lock(mutex_);
            local_callbacks = callbacks_;
        }

        // Execute outside lock (VERY IMPORTANT)
        for (auto& cb : local_callbacks) {
            cb();
        }
    }

private:
    std::vector<Callback> callbacks_;
    std::mutex mutex_;
};

/*
1) Use shared_mutex (read-heavy optimization)
If event_fired is frequent:

#include <shared_mutex>
std::shared_mutex mutex_;

register_callback → unique_lock
event_fired → shared_lock

2) Async Execution (Thread Pool)
for (auto& cb : local_callbacks)
    thread_pool.enqueue(cb);

3) Handle Unregister
int register_callback(Callback cb);
void unregister_callback(int id);

std::unordered_map<int, Callback>

*/

    
int main()
{
    fastio();
    
    return 0;
}