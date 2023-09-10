#include "Bitboard.h"

Bitboard::Bitboard() : board(0) {}

Bitboard::Bitboard(std::uint64_t init) : board(init) {}

void Bitboard::setSquare(int position) {
    board |= (1ULL << position);
}

void Bitboard::clearSquare(int position) {
    board &= ~(1ULL << position);
}

bool Bitboard::getSquare(int position) const {
    return board & (1ULL << position);
}

int Bitboard::countBits() const {
		return __builtin_popcountll(board);
}

int Bitboard::getLSB() const {
		return __builtin_ctzll(board);
}

int Bitboard::popLSB() {
		int lsb = getLSB();
		clearSquare(lsb);
		return lsb;
}

Bitboard Bitboard::northOne() const {
		return *this << 8;
}

Bitboard Bitboard::southOne() const {
		return *this >> 8;
}

Bitboard Bitboard::eastOne() const {
		return *this << 1 & ~Bitboard(0x0101010101010101ULL);
}

Bitboard Bitboard::westOne() const {
		return *this >> 1 & ~Bitboard(0x8080808080808080ULL);
}

Bitboard Bitboard::northEastOne() const {
		return *this << 9 & ~Bitboard(0x0101010101010101ULL);
}

Bitboard Bitboard::northWestOne() const {
		return *this << 7 & ~Bitboard(0x8080808080808080ULL);
}

Bitboard Bitboard::southEastOne() const {
		return *this >> 7 & ~Bitboard(0x0101010101010101ULL);
}

Bitboard Bitboard::southWestOne() const {
		return *this >> 9 & ~Bitboard(0x8080808080808080ULL);
}

bool Bitboard::operator==(const Bitboard& other) const {
		return board == other.board;
}

Bitboard Bitboard::operator|(const Bitboard& other) const {
    return Bitboard(board | other.board);
}

Bitboard Bitboard::operator&(const Bitboard& other) const {
    return Bitboard(board & other.board);
}

Bitboard Bitboard::operator^(const Bitboard& other) const {
		return Bitboard(board ^ other.board);
}

Bitboard Bitboard::operator~() const {
		return Bitboard(~board);
}

Bitboard Bitboard::operator<<(int shift) const {
		return Bitboard(board << shift);
}

Bitboard Bitboard::operator>>(int shift) const {
		return Bitboard(board >> shift);
}

Bitboard& Bitboard::operator|=(const Bitboard& other) {
    board |= other.board;
    return *this;
}

Bitboard& Bitboard::operator&=(const Bitboard& other) {
    board &= other.board;
    return *this;
}

Bitboard& Bitboard::operator^=(const Bitboard& other) {
		board ^= other.board;
		return *this;
}

Bitboard& Bitboard::operator<<=(int shift) {
		board <<= shift;
		return *this;
}

Bitboard& Bitboard::operator>>=(int shift) {
		board >>= shift;
		return *this;
}

void Bitboard::pprint() const {
    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            int position = rank * 8 + file;
            std::cout << (getSquare(position) ? "1" : "0") << " ";
        }
        std::cout << "\n";
    }
}
