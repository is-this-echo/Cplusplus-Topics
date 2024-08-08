/*
TOPIC : Use of join(), detach() & joinable() in std::thread from C++ 11 onwards

Notes on Join :
---------------
1. Once a thread is started we wait for this thread to finish by calling
   join() function on the thread object.
2. Double join will result into program termination.
3. If needed we should check thread is joinable before joining using joinable().

Notes on Detach :
-----------------
1. This is used to detach newly created thread from the parent thread.
2. Always check before detaching a thread that it is joinable otherwise we
   may end up double detaching and double detach() will result into program termination.
3. If we have detached thread and main function is returning then the detached thread
   execution is suspended.

Either join() or detach() should be called on thread object, otherwise in thread
object's destructor call it will terminate the program. Because, inside destructor
it checks if thread is still joinable, if "yes" it terminates the program.

*/

#include<iostream>
#include<chrono>
#include<thread>

void run(int x)
{
    while (x-- > 0)
        std::cout << "thread1" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

int main()
{
    std::thread t1(run, 5); // thread created with joinable property as true

    // below line is executed first in output as the OS takes some time to create thread and run it
    std::cout << "main()" << std::endl; 
    // t1.join();
    // t1.join(); // a 2nd join call throws error as thread already completed/joined

    // if (t1.joinable())
    //     t1.join();

    // If we use detach, the parent thread doesn't wait for the child thread
    // and program can terminate before child thread has finished execution as
    // main thread has completed and hit return 0, if main thread waits for long
    // then maybe child thread finishes execution and we can see the desired output.
    t1.detach(); 
    // t1.detach() // a 2nd detach call throws error as thread already completed/detached

    // if (t1.joinable())
    //     t1.detach();

    std::cout << "main() after thread" << std::endl;

    return 0;
}