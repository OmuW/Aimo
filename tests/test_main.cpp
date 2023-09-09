#define CATCH_CONFIG_MAIN  // This tells Catch2 to provide a main() - only do this in one cpp file
#include <catch2/catch_all.hpp>
#include "fib.h"

TEST_CASE("Fibonacci Tests") {
    REQUIRE(fib(0) == 0);
    REQUIRE(fib(1) == 1);
    REQUIRE(fib(2) == 1);
    REQUIRE(fib(3) == 2);
    REQUIRE(fib(4) == 3);
    REQUIRE(fib(5) == 5);
    REQUIRE(fib(6) == 8);
}
