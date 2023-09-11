#pragma once
#include <vector>
#include "Board.h"
#include "Bitboard.h"

class Movegen {
private:
    Board& board;

    void generatePawnMoves(std::vector<Move>& moveList);
public:
    Movegen(Board& b) : board(b) {}

    std::vector<Move> generateLegalMoves();
};
