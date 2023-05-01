#include<iostream>

template <typename T>
class Pair {
private:
    T first;
    T second;

public:
    Pair(T f, T s) : first(f), second(s) {}
    
    T GetFirst() const { return first; }
    T GetSecond() const { return second; }
};


int main()
{
    
 Pair<int> PInt(3,4);
 std::cout << PInt.GetFirst() << " " << PInt.GetSecond() << std::endl;

 Pair<std::string> PStr("before", "after");
 std::cout << PStr.GetSecond() << " " << PStr.GetFirst() << std::endl;

    return 0;
}