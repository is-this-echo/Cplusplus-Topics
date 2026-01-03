# include<bits/stdc++.h>
# include <concepts>
using namespace std;


template <typename T>
requires std::integral<T>
bool isEqual(const T& a, const T& b)
{
    return a == b;
}


int main()
{
    std::cout << std::boolalpha << isEqual(12, 11);

    return 0;
}
