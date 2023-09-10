#ifndef BOARD_H
#define BOARD_H
#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "Bitboard.h"
#include "chess_utils.h"

enum Piece { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, PIECE_COUNT };
enum Color { WHITE, BLACK, COLOR_COUNT };
enum CastlingRights {
    WHITE_KING_SIDE = 1,
    WHITE_QUEEN_SIDE = 2,
    BLACK_KING_SIDE = 4,
    BLACK_QUEEN_SIDE = 8
};
extern std::array<std::array<std::string, PIECE_COUNT>, COLOR_COUNT> pieceStrings; 

class Board {
private:
    std::array<std::array<Bitboard, PIECE_COUNT>, COLOR_COUNT> board;

    Color activeColor;
    std::uint8_t castlingRights; // 4 bits for each castling right.
    Bitboard enPassant; // The en passant square, if any. If no en passant square, this is 0.
    int halfMoveClock; // The number of half moves since the last capture or pawn advance.
    int fullMoveNumber;

public:
    Board(); // Initializes the board to its starting position.
    Board(std::string& fen);
    // TODO: Add a constructor that takes a Board and a Move and returns a new Board. 
    // NOTE: this will need make/unmake move functions.
    
    Bitboard getBitboard(Piece piece, Color color) const;
    void setBitboard(Piece piece, Color color, const Bitboard& bitboard);

    std::string toFen() const;
    void pprint() const;
};

#endif