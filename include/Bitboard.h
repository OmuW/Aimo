#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>
#include <iostream>

class Bitboard {
private:
    std::uint64_t board;

public:
    // Constructors
    Bitboard();
    explicit Bitboard(std::uint64_t init);

    // Basic operations
    void setSquare(int position);
    void clearSquare(int position);
    bool getSquare(int position) const;

    // Bitwise operations
    Bitboard operator|(const Bitboard& other) const;
    Bitboard operator&(const Bitboard& other) const;
    Bitboard& operator|=(const Bitboard& other);
    Bitboard& operator&=(const Bitboard& other);

    // Display function for debugging
    void pprint() const;
};

#endif // BITBOARD_H

