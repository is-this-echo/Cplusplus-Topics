#include <iostream>


template <typename T>
struct Rank
{
    static constexpr size_t value = 0;
};

// int arr[] = {1, 2, 3, 4};
// partial  specialization, strips of the first dimension of unknow size
template <typename T>
struct Rank<T[]>
{
    static constexpr size_t value = 1u + Rank<T>::value;
};

// int arr[4] = {1, 2, 3, 4};
// partial specialization, strips off the first dimension
template <typename T, size_t N>
struct Rank<T[N]>
{
    static constexpr size_t value = 1u + Rank<T>::value;
};

// Check out https://cppinsights.io/s/e7141df3 for template instantiation by compiler

int main()
{
    static_assert(Rank<int>::value == 0);
    static_assert(Rank<float[3]>::value == 1);
    static_assert(Rank<float[3][3]>::value == 2);
    static_assert(Rank<char[3][3][2][10]>::value == 4);

    return 0;
}