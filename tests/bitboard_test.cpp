#include <catch2/catch_all.hpp>
#include "Bitboard.h"

TEST_CASE("Bitboard Operations", "[bitboard]") {
    Bitboard b;

    SECTION("Default Constructor") {
        REQUIRE(b.getSquare(0) == false);
    }

    SECTION("Setting and Clearing Squares") {
        b.setSquare(0);
        REQUIRE(b.getSquare(0) == true);
        b.clearSquare(0);
        REQUIRE(b.getSquare(0) == false);
    }

    SECTION("Bitwise Operations") {
        Bitboard b1(0b1010);
        Bitboard b2(0b1100);
        Bitboard result;

        result = b1 | b2;
        REQUIRE((result.getSquare(3) == true && result.getSquare(2) == true));

        result = b1 & b2;
        REQUIRE(result.getSquare(0) == false);
    }
}
