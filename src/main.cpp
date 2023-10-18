#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Board.h"
#include "Movegen.h"
#include "Evaluation.h"

int main() {
    std::string fen = "8/pppppppp/8/8/8/8/PPPPPPPP/8 w - - 0 1";
    Board board(fen);
    board.pprint();

    srand(time(NULL));

    Movegen movegen(board);
    std::vector<Move> moves = movegen.generateLegalMoves();
    while (moves.size() > 0) {
        Move move = moves[rand() % moves.size()];
        board.makeMove(move);
        board.pprint();
        std::cout << "Evaluation: " << evaluate(board) << std::endl;
        moves = movegen.generateLegalMoves();
    }
    

    return 0;
}
