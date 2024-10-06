/*
TOPIC : Mutex try_lock() in C++ multi-threading

Notes on std::mutex::try_lock() :
--------------------------------
1. try_lock() tries to lock the mutex. Returns immediately. On successful lock acquisition
   returns true otherwise returns false.
2. If try_lock() is not able to lock mutex, then it doesn't get blocked, so non-blocking.
3. If try_lock() is called again by the same thread which owns the mutex, the behaivour
   is undefined. This will be a dead lock situation. (For locking the same mutex by the same
   thread more than once, go for recursive_mutex).

*/

#include<iostream>
#include<thread>
#include<mutex>

constexpr int cycle = 1000000;
int value = 0;
std::mutex mtx;

void IncrementUptoCycleTimes()
{
    for(int i = 0; i < cycle; i++)
    {
        if (mtx.try_lock())
        {
            value++;
            mtx.unlock();
        }
    }
}


int main()
{
    std::thread t1(IncrementUptoCycleTimes);
    std::thread t2(IncrementUptoCycleTimes);

    // Here, results are undefined and very less than 2000000 because here the 2nd thread
    // doesn't wait for the mutex to get unlocked, it returns when if check is false and i
    // increments but still mutex is locked and being used by the other thread & vice versa.
    // So, the main reason behind erratic result is skipping of iterations.
    t1.join();
    t2.join();

    std::cout << "Value after execution of both threads: " << value;
}
