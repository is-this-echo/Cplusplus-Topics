#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstddef>  // for std::size_t


template <typename T>
struct PoolAllocator
{
    /*
    The C++ Standard Library expects allocators to define certain types and functions
    if they want to work with standard containers. value_type is simply an alias inside your allocator that tells the STL “this allocator allocates objects of type T”.
    PoolAllocator<int>::value_type -> int

    STL containers are templates that depend on allocators.
    When std::vector<int, PoolAllocator<int>> is compiled, the vector sometimes needs to ask the allocator questions like:
    1) What type of object do you allocate?
    2) What type do I get if I rebind the allocator for a different type
        (e.g., nodes, internal    structures)?

    Instead of hardcoding "the template parameter is T", the STL uses allocator traits (std::allocator_traits) which standardize the interface.

    std::allocator_traits<PoolAllocator<int>>::value_type will look up your value_type and get int.
    If you don’t provide it, allocator_traits won’t know what your allocator allocates → the container won’t
    */
    using value_type = T;

    PoolAllocator() : offset(0) {}

    // Allocate n objects of type T
    T* allocate(std::size_t n)
    {
        std::size_t bytesNeeded = n * sizeof(T);

        // Check if memory is available
        if (offset + bytesNeeded > sizeof(mempool)) {
            throw std::bad_alloc();
        }

        T* ptr = reinterpret_cast<T*>(mempool + offset);
        offset += bytesNeeded;

        return ptr;
    }

    // Deallocate memory - no-op for simple bump allocator
    void deallocate(T* ptr, std::size_t /*n*/)
    {
        // Do nothing — memory is freed when the pool is destroyed
    }

    // STL requires this for compatibility
    template <typename U>
    struct rebind
    {
        using other = PoolAllocator<U>;
    };

    char mempool[5000];
    std::size_t offset;
};


int main() {
    // Use vector with custom allocator
    std::vector<int, PoolAllocator<int>> vec;
    for (int i = 0; i < 500; i++)
        vec.push_back(i * 10);

    for (int v : vec)
        std::cout << v << " ";

    std::cout << std::endl;

    std::vector<char, PoolAllocator<char>> vec2;
    for (auto ch = 'a'; ch <= 'z'; ++ch)
        vec2.emplace_back(ch);
    for (const auto ch : vec2)
        std::cout << ch << " ";



    return 0;
}
