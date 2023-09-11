#include <iostream>
#include <string>
#include "Board.h"
#include "Movegen.h"

int main() {
    std::string fen = "8/8/8/8/8/7p/PPPPPPPP/8 w - - 0 1";
    Board pawnBoard(fen);

    std::string black_fen = "8/pppppppP/8/8/8/8/8/8 b - h6 0 1";
    Board blackBoard(black_fen);

    Movegen generator(pawnBoard);
    Movegen blackGenerator(blackBoard);

    std::vector<Move> moves = generator.generateLegalMoves(Color::WHITE);
    pawnBoard.pprint();

    std::cout << "Legal moves: " << moves.size() << std::endl;

    std::vector<Move> black_moves = blackGenerator.generateLegalMoves(Color::BLACK);
    blackBoard.pprint();

    std::cout << "Legal moves: " << black_moves.size() << std::endl;

    return 0;
}
