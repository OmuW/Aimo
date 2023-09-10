#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>
#include <iostream>

/**
 * A class representing a 64-bit bitboard.
 */
class Bitboard {
private:
    std::uint64_t board;

public:
    Bitboard();
    explicit Bitboard(std::uint64_t init);

    void setSquare(int position);
    void clearSquare(int position);
    bool getSquare(int position) const;
		int countBits() const;
		int getLSB() const;
		int popLSB();
		Bitboard northOne() const;
		Bitboard southOne() const;
		Bitboard eastOne() const;
		Bitboard westOne() const;
		Bitboard northEastOne() const;
		Bitboard northWestOne() const;
		Bitboard southEastOne() const;
		Bitboard southWestOne() const;

		bool operator==(const Bitboard& other) const;

    Bitboard operator|(const Bitboard& other) const;
    Bitboard operator&(const Bitboard& other) const;
		Bitboard operator^(const Bitboard& other) const;
		Bitboard operator~() const;
		Bitboard operator<<(int shift) const;
		Bitboard operator>>(int shift) const;

    Bitboard& operator|=(const Bitboard& other);
    Bitboard& operator&=(const Bitboard& other);
		Bitboard& operator^=(const Bitboard& other);
		Bitboard& operator<<=(int shift);
		Bitboard& operator>>=(int shift);

		// pprint() is short for pretty print, feel free to change this.
    void pprint() const;
};

#endif // BITBOARD_H