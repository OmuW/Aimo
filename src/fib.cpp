#include "fib.h"
ull fib(ull n)
{
	if (n <= 1)
		return n;
	return fib(n - 1) + fib(n - 2);
}