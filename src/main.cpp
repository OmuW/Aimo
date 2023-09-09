#include <iostream>
#include "fib.h"

int main()
{
	ull number;
	std::cout << "Enter the position for Fibonacci sequence: ";
	std::cin >> number;
	std::cout << "The Fibonacci number at position" << number << " is: "
		<< fib(number) << std::endl;
	return 0;
}
