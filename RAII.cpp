
/*
TOPIC : Resource Acquisition is Initialization (RAII)

Reference : https://learn.microsoft.com/en-us/cpp/cpp/object-lifetime-and-resource-management-modern-cpp

Notes on Object lifetime and resource management:
------------------------------------------------
1. Unlike managed languages, C++ doesn't have automatic garbage collection, an internal process
   that  releases heap memory and other resources as a program runs.
   A C++ program is responsible for returning all acquired resources to the operating system.
   Failure to release an unused resource is called a leak. Leaked resources are unavailable to
   other programs until the process exits (as we know that each process has its own memory space).

2. When we say 'Resource' we don't just mean memory - it could be file handles, network sockets,
   database handles, GDI objects and mutexes. In short, things that we have a finite supply of and so we
   need to be able to control their usage.
   The 'Scope-bound' aspect means that the lifetime of the object is bound to the scope of a
   variable, so when the variable goes out of scope then the destructor will release the resource.
   A very useful property of this is that it makes for greater exception-safety.

   **
    When a resource-owning stack object goes out of scope, its destructor is automatically invoked.
    In this way, garbage collection in C++ is closely related to object lifetime, and is
    deterministic.
   **

3. Modern C++ avoids using heap memory as much as possible by declaring objects on the stack.
   When a  resource is too large for the stack, then it should be owned by an object.
   As the object gets initialized, it acquires the resource it owns. The object is then responsible
   for releasing the resource in its destructor. The owning object itself is declared on the stack.The principle that objects own resources is also known as "resource acquisition is initialization," or RAII.

4. Exception handlling example -

    a) Without implementing RAII
    .....
    RawResourceHandle* handle=createNewResource();
    handle->performInvalidOperation();  // Oops, throws exception
    deleteResource(handle); // never gets called so the resource leaks


    b) With the RAII one
    .....
    class ManagedResourceHandle {
    public:
    ManagedResourceHandle(RawResourceHandle* rawHandle_) : rawHandle(rawHandle_) {};
    ~ManagedResourceHandle() {delete rawHandle; }
    ... // omitted operator*, etc
    private:
    RawResourceHandle* rawHandle;
    };

    ManagedResourceHandle handle(createNewResource());
    handle->performInvalidOperation();  // Oops, throws exception 
    // still destructor called when object goes out of scope

*/

#include<iostream>
#include<memory>

/*
 * The following example shows a simple object w. It's declared on the stack at function
 * scope, and is destroyed at the end of the function block. The object w owns no resources
 * (such as heap-allocated memory). Its only member g is itself declared on the stack,
 * and simply goes out of scope along with w. No special code is needed in the widget destructor.
*/
struct Gadget
{
    std::pair<int, int> userInfo;

    Gadget(int userId = 0, int passkey = 0) : userInfo{userId, passkey} {}
    ~Gadget()
    {
        std::cout << "Gadget object destructed successfully! \n";
    }
};

class Widget {
private:
    Gadget g;   // lifetime automatically tied to enclosing object

public:
    void draw() {};
};

void functionUsingWidget ()
{
    Widget w;   // lifetime automatically tied to enclosing scope
                // constructs w, including the w.g Gadget member
    // ...
    w.draw();
    // ...
} // automatic destruction and deallocation for w and w.g
  // automatic exception safety as if "finally { w.dispose(); w.g.dispose(); }"


/*
 * In the following example, w owns a memory resource and so must have code
 * in its destructor to delete the memory else it will lead to memory leak.
*/
class WidgetHeap
{
private:
    int* data;
    // std::unique_ptr<int[]> data;
public:
    WidgetHeap(const int size)
    {
        data = new int[size]; // acquire memory
        // data = std::make_unique<int[]>(size);
    }
    ~WidgetHeap() // not required if we use smart pointers
    {
        delete[] data; // release memory
        std::cout << "WidgetHeap object destructed successfully! \n";
    } 

    void do_something() {}
};

void functionUsingWidgetHeap() {
    WidgetHeap w(1000000);  // lifetime automatically tied to enclosing scope
                        // constructs w, including the w.data member
    w.do_something();

} // automatic destruction and deallocation for w and w.data



int main()
{
    // functionUsingWidget();
    functionUsingWidgetHeap();

    return 0;
}
