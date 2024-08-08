/*
TOPIC : Types of thread creation in C++ 11 and above.
There are mainly 5 different ways of creating threads using callable objects.

Note : If we create multiple threads at the same time, we don't know for sure
which one will start first.

*/

#include<iostream>
#include<thread>

// 1. Function pointers
// The most basic way of creating threads
void func(int x)
{
    while (x-- > 0)
        std::cout << x << std::endl;
}

int main()
{
    std::thread t1(func, 11);
    t1.join();

    return 0;
}

// 2. Lambda function
// we can directly insert lambda at thread creation time
int main()
{
    auto func = [](int x)
    {
        while (x-- > 0)
            std::cout << x << std::endl;
    };

    // std::thread t(func, 10);
    std::thread t( [](int x)
                {
                    while (x-- > 0)
                        std::cout << x << std::endl;
                }, 10);
    t.join();

    return 0;   
}

// 3. Functor (function object)
class Base 
{
public:
    void operator ()(int x)
    {
        while (x-- > 0)
            std::cout << x << std::endl;
    }
};

int main()
{
    std::thread t(Base(), 10);
    t.join();

    return 0;   
}

// 4. Non-static member function
class Base 
{
public:
    void run(int x)
    {
        while (x-- > 0)
            std::cout << x << std::endl;
    }
};

int main()
{
    Base b;
    std::thread t(&Base::run, &b, 10);  // parameters : function pointer, obj reference, value
    t.join();

    return 0;   
}

// 5. Static member function
class Base 
{
public:
    static void run(int x)
    {
        while (x-- > 0)
            std::cout << x << std::endl;
    }
};

int main()
{
    std::thread t(&Base::run, 10);  // parameters : function pointer, value
    t.join();

    return 0;   
}
