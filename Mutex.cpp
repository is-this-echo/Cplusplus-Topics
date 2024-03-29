#include<iostream>
#include<thread>
#include<mutex>

constexpr int cycle = 1000000;
int value = 0;

std::mutex mtx;


void Increment()
{
    for(int i=0; i<cycle; i++)
        value++;
}


void IncrementWithThreadSync()
{
    mtx.lock();

    for(int i=0; i<cycle; i++)
        value++;

    mtx.unlock();
}


int main()
{
    std::thread t1(Increment);
    std::thread t2(Increment);

    // thread t1(IncrementWithThreadSync);
    // thread t2(IncrementWithThreadSync);

    t1.join();
    t2.join();

    std::cout << "Value after execution of both threads: " << value;
}