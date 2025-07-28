#include <iostream>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <thread>


class FooBar
{
public:
    FooBar(int n = 5) : n(n), isFooPrinted(false) {}

    void foo(std::function<void()> printFoo)
    {
        for (int i = 0; i < n; i++)
        {
            std::unique_lock<std::mutex> lck(mtx_);
            // thread will wake up and continue processing
            // only when condition is true
            cv_.wait(lck, [this](){ return !isFooPrinted; });

        	printFoo();
            isFooPrinted = true;
            // notify all other sleeping threads that condition has changed,
            // wake up and do your thing
            cv_.notify_all(); 
        }
    }

    void bar(std::function<void()> printBar)
    {
        for (int i = 0; i < n; i++)
        {
            std::unique_lock<std::mutex> lck(mtx_);
            // thread will wait/sleep until condition is true,
            // till then release/unlock the mutex for other threads to use
            cv_.wait(lck, [this](){ return isFooPrinted; });

        	printBar();
            isFooPrinted = false;
            cv_.notify_all();
        }
    }

private:
    int n;
    bool isFooPrinted;
    std::mutex mtx_;
    std::condition_variable cv_;
};


int main()
{
    FooBar fb;
    std::thread t1(&FooBar::bar, &fb, [](){ std::cout << "bar\n"; });
    std::thread t2(&FooBar::foo, &fb, [](){ std::cout << "foo"; });

    /*
    std::thread t1, t2;
    t1(fb.bar, [](){ std::cout << "bar"; }); // ❌ Invalid

    This fails because :
    --------------------
    1) fb.bar is a non-static member function.
    2) Non-static member functions have an implicit this pointer and need an object instance to be called.
    3) You cannot call t1(...) like a function to launch a thread.

    Correct approach :
    -----------------
        std::thread t1([&fb]() {
            fb.bar([]() { std::cout << "bar"; });
        });
        std::thread t2([&fb]() {
            fb.foo([]() { std::cout << "foo"; });
        });
    */

    t1.join();
    t2.join();

    return 0;
}