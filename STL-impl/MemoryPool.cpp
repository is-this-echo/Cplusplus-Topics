#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstddef>  // for std::size_t

template <typename T>
struct PoolAllocator
{
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

    for (int i = 0; i < 5000; i++) {
        vec.push_back(i * 10);
    }

    for (int v : vec) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    return 0;
}
