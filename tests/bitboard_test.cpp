#include <catch2/catch_all.hpp>
#include "Bitboard.h"

// NOTE: these tests are nowhere near complete
// TODO: add more tests to handle all cases

TEST_CASE("Bitboard Operations", "[bitboard]") {
    Bitboard b;

    SECTION("Default Constructor") {
        REQUIRE(b.getSquare(0) == false);
    }

    SECTION("Initialization and Basic Operations") {
        Bitboard b1(0b1001);
        REQUIRE(b1.getSquare(0) == true);
        REQUIRE(b1.getSquare(3) == true);
        
        b1.setSquare(1);
        REQUIRE(b1.getSquare(1) == true);
        
        b1.clearSquare(1);
        REQUIRE(b1.getSquare(1) == false);
    }

    SECTION("Bit Manipulation") {
        Bitboard b1(0b1101);
        REQUIRE(b1.countBits() == 3);
        REQUIRE(b1.getLSB() == 0);
        REQUIRE(b1.popLSB() == 0);
        REQUIRE(b1.getSquare(0) == false);
    }

    SECTION("Shifting and Movement") {
        Bitboard b1(0b1);
        REQUIRE((b1.northOne().getSquare(8) == true));
        REQUIRE((b1.southOne().getSquare(0) == false)); // No change, as it can't go further south
        REQUIRE((b1.eastOne().getSquare(1) == true));
        REQUIRE((b1.westOne().getSquare(0) == false)); // Similarly, no change for west
        REQUIRE((b1.northEastOne().getSquare(9) == true));
        REQUIRE((b1.northWestOne().getSquare(7) == false)); // No change for northWest
        REQUIRE((b1.southEastOne().getSquare(1) == false)); // No change for southEast
        REQUIRE((b1.southWestOne().getSquare(0) == false)); // No change for southWest
    }

    SECTION("Bitwise Operations") {
        Bitboard b1(0b1010);
        Bitboard b2(0b1100);
        REQUIRE(((b1 | b2).countBits() == 3));
        REQUIRE(((b1 & b2).countBits() == 1));
        REQUIRE(((b1 ^ b2).countBits() == 2));
        REQUIRE(((~b1).getSquare(3) == false));
        
        b1 |= b2;
        REQUIRE(b1.countBits() == 3);

        b1 = Bitboard(0b1010);
        b2 = Bitboard(0b1100);
        b1 &= b2;
        REQUIRE(b1.countBits() == 1);

        b1 = Bitboard(0b1010);
        b2 = Bitboard(0b1100);
        b1 ^= b2;
        REQUIRE(b1.countBits() == 2);

        b1 = Bitboard(0b1010);
        b2 = Bitboard(0b1100);
        b1 <<= 2;
        b2 >>= 2;
        REQUIRE(b1.countBits() == 2);
        REQUIRE(b2 == Bitboard(0b0011));

    }

    SECTION("Shift Operators") {
        Bitboard b1(0b1);
        REQUIRE((b1 << 2).getSquare(2) == true);
        REQUIRE((b1 >> 1).getSquare(0) == false);
        
        b1 <<= 2;
        REQUIRE(b1.getSquare(2) == true);
        b1 >>= 2;
        REQUIRE(b1.getSquare(0) == true);
    }
}
