#include<iostream>
#include<vector>


void Calculate(int num)
{
    std::cout << "Modified value is " << num*num/2 << std::endl;
}


/**
 * @brief This function prints the value of the passed number 
 * 
 * @param num An integer value  
 */
void PrintValue(int num)
{
    std::cout << "Value is " << num << std::endl;
}


/**
 * An example of usage of function pointers
 * 
 * @param nums Vector of numbers for operation
 * @param func Pointer to a function, replace func with any name you want
 */
void ForEach(std::vector<int> &nums, void(*func)(int)) 
{
    for(int x : nums)
        func(x);
}


int main()
{
    std::vector<int> nums = {12,23,66,90,5,147,54,722};

    ForEach(nums, Calculate);
    ForEach(nums, PrintValue);
    ForEach(nums, [](int num){ std::cout<< " Adding 10 to value : " << num + 10 << std::endl; });

    return 0;

}