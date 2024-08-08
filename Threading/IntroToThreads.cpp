/*
TOPIC : Threading in C++ (C++ 11 onwards)

- In every application there is default thread which is the main thread (running the main() function),
  we can create other threads . A thread can also be thought of as a lightweight process.
  The idea is to achieve parallelism by dividing a process into multiple threads.

  Example of multiple threads being used:
  =======================================
  1) Chrome browser has each tab running on a different thread.
  2) MS Word uses one thread to format the text, a different thread to process inputs (spell checker).
  3) VS Code editor uses multiple threads for features - auto completion(Intellisense), linting etc.

- Ways to create threads in C++11 and onwards
  1) Function pointers
  2) Lambda functions
  3) Functors
  4) Non-static member functions
  5) Static member functions

*/

#include<iostream>
#include<thread>
#include<chrono>
#include<algorithm>

typedef unsigned long long ull;
using namespace std;
using namespace std::chrono;

// Find the sum of all odd & even numbers from 1 to 1900000000
ull evenSum = 0;
ull oddSum = 0;

void findEvenSum(ull start, ull end)
{
    for (ull i = start; i <= end; ++i)
        if ((i & 1) == 0)
            evenSum += i;
}

void findOddSum(ull start, ull end)
{
    for (ull i = start; i <= end; ++i)
        if ((i & 1) == 1)
            oddSum += i;
}

int main()
{
    ull start = 0, end = 1900000000;
    auto startTime = high_resolution_clock::now();

    // functions run parallely in different threads
    std::thread t1(findEvenSum, start, end); // running findEvenSum() in t1
    std::thread t2(findOddSum, start, end); // running findOddSum() in t2

    // required to connect the other threads to the main thread
    t1.join();  // wait for thread t1 to complete
    t2.join(); // wait for thread t2 to complete

    // findEvenSum(start, end);
    // findOddSum(start, end);

    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stopTime - startTime);

    cout << "EvenSum : " << evenSum << "\n";
    cout << "OddSum : " << oddSum << "\n";
    cout << "Seconds : " << duration.count() << endl;

    return 0;
}