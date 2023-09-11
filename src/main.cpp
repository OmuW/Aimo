#include <iostream>
#include <string>
#include <cstdlib>
#include "Board.h"
#include "Movegen.h"

int main() {
    std::string fen = "8/pppppppp/8/8/8/8/PPPPPPPP/8 w - - 0 1";
    Board board(fen);
    board.pprint();

    Movegen movegen(board);

    for (int i = 0; i < 40; i++) {
        std::vector<Move> moves = movegen.generateLegalMoves();
        Move move = moves[rand() % moves.size()];
        board.makeMove(move);
        board.pprint();

    }

    return 0;
}
