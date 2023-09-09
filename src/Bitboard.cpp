#include "Bitboard.h"

// Constructors
Bitboard::Bitboard() : board(0) {}

Bitboard::Bitboard(std::uint64_t init) : board(init) {}

// Basic operations
void Bitboard::setSquare(int position) {
    board |= (1ULL << position);
}

void Bitboard::clearSquare(int position) {
    board &= ~(1ULL << position);
}

bool Bitboard::getSquare(int position) const {
    return board & (1ULL << position);
}

// Bitwise operations
Bitboard Bitboard::operator|(const Bitboard& other) const {
    return Bitboard(board | other.board);
}

Bitboard Bitboard::operator&(const Bitboard& other) const {
    return Bitboard(board & other.board);
}

Bitboard& Bitboard::operator|=(const Bitboard& other) {
    board |= other.board;
    return *this;
}

Bitboard& Bitboard::operator&=(const Bitboard& other) {
    board &= other.board;
    return *this;
}

// Display function for debugging
void Bitboard::pprint() const {
    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            int position = rank * 8 + file;
            std::cout << (getSquare(position) ? "1" : "0") << " ";
        }
        std::cout << "\n";
    }
}
