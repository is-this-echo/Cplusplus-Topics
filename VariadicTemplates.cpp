
/*
TOPIC : Variadic templates

Notes on Ellipsis and Variadic templates:
------------------------------------------------
1. A variadic template is a class or function template that supports an arbitrary
   number of arguments. This mechanism is especially useful to C++ library developers:
   You can apply it to both class templates and function templates, and thereby
   provide a wide range of type-safe and non-trivial functionality and flexibility.

2. Ellipsis used to the left of the parameter name signifies a parameter pack.
   If used to the right of the parameter name, it expands the parameter packs
   into separate names which is common in function arguments.
   White spaces can be used around the ellipsis at will

   All below examples are valid parameter packs -
   template<typename... Arguments>
   template<typename ...Arguments>
   template<typename ... Arguments>

   One example of parameter pack in the function arguments -
   template <typename... Arguments> returntype functionname(Arguments... args);

   // v1 is NOT a function parameter pack, we can't have multiple types in std::vector
   template <typename... Types> void func1(std::vector<Types...> v1);

   // v2 IS a function parameter pack
   template <typename... Types> void func2(std::vector<Types>... v2);

   Usage for above function template : 
   func2(std::vector<int>{}, std::vector<double>{}) ;

*/

#include <iostream>

/**
 * @brief To handle base case of below recursive variadic function template
 */
void print()
{
	std::cout << "I don't take any arguments, "
			     "I am called at last. \n";
}

/**
 * @brief Variadic function template that takes variable number of arguments
 * and prints all of them, function call with >= 1 argument gets matched here
 * 
 * @param var 
 * @param var2
 * @return template <typename T, typename... Types>
 */
template <typename T, typename... Types>
void print(T arg1, Types... arg2) // function argument receiving a parameter pack
{
	std::cout << arg1 << std::endl;

	print(arg2...); // recursive call using pack expansion syntax
}


int main()
{
	print(1, 2, 3.14,
		"Pass me any number of arguments",
		"I will print them all \n");

	return 0;
}
