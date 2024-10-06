/*
TOPIC : Mutex in C++ threading

Notes on Race condition :
-------------------------
1. Race condition is a situation where two or more threads/process tries to access/modify
   a shared resource/data simultaneously.
   t1 -> read, t2-> read  : no race condition
   t1 -> read, t2-> write  : can lead to a race condition
   t1 -> write, t2-> read  : can lead to a race condition
   t1 -> write, t2-> write  : can lead to a race condition

2. If there is a race condition then we have to protect it, the protected section
   is called critical section/region.

Notes on Mutex (Mutual Exclusion) :
---------------------------------
1. Mutex is used to avoid race condition / implement thread synchronization.
2. We can use lock(), unlock() on mutex for thread synchronization.
3. If mutex is locked by one thread, then the other thread(s) trying to access it with get blocked.

*/

#include<iostream>
#include<thread>
#include<mutex>

constexpr int cycle = 1000000;
int value = 0;
std::mutex mtx;

void Increment()
{
    for (int i = 0; i < cycle; i++) // critical section guarded by lock
        value++;
}

void IncrementWithThreadSync()
{
    mtx.lock(); // resource(mutex) is locked by the first thread that reaches here
    for(int i = 0; i < cycle; i++) 
        value++;    // critical section guarded by lock
    mtx.unlock();
}


int main()
{
    // std::thread t1(Increment);
    // std::thread t2(Increment);
    std::thread t1(IncrementWithThreadSync);
    std::thread t2(IncrementWithThreadSync);

    t1.join();
    t2.join();

    std::cout << "Value after execution of both threads: " << value;
}
