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
enum MoveType {
    NORMAL,
    PAWN_DOUBLE_MOVE,
    CAPTURE,
    EN_PASSANT,
    CASTLING,
    PROMOTION
};

class Move {
private:
    int to;
    int from;
    MoveType moveType;
    Piece promotionPiece;
    Piece capturedPiece;
public:
    Move();
    Move(int to, int from, MoveType moveType);
    
    void setPromotionPiece(Piece promotionPiece);
    void setCapturedPiece(Piece capturedPiece);

    MoveType getMoveType();
    Piece getPromotionPiece();
    Piece getCapturedPiece();
};

extern std::array<std::array<std::string, PIECE_COUNT>, COLOR_COUNT> pieceStrings; 

class Board {
private:
    std::array<std::array<Bitboard, PIECE_COUNT>, COLOR_COUNT> board;
    Bitboard occupiedSquares;
    Bitboard emptySquares;

    Color activeColor;
    std::uint8_t castlingRights; // 4 bits for each castling right.
    Bitboard enPassant; // The en passant square, if any. If no en passant square, this is 0.
    int halfMoveClock; // The number of half moves since the last capture or pawn advance.
    int fullMoveNumber;

    Move lastMove;

public:
    Board(); // Initializes the board to its starting position.
    Board(std::string& fen);
    // TODO: Add a constructor that takes a Board and a Move and returns a new Board. 
    // NOTE: this will need make/unmake move functions.
    
    Bitboard getBitboard(Color color, Piece piece) const;
    void setBitboard(Color color, Piece piece, const Bitboard& bitboard);

    Bitboard getOccupiedSquares() const;
    Bitboard getEmptySquares() const;
    void setOccupiedSquares(const Bitboard& occupiedSquares);
    void setEmptySquares(const Bitboard& emptySquares);

    std::string toFen() const;
    void pprint() const;
};

#endif