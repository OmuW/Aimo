#include "Movegen.h"

void Movegen::generatePawnMoves(Color color, std::vector<Move>& moveList) {
    Bitboard pawns;
    Bitboard emptySquares = board.getEmptySquares();
    Bitboard pawnMoves, doublePawnMoves;

    if(color == WHITE) {
        pawns = board.getBitboard(WHITE, PAWN);
        
        pawnMoves = (pawns << 8) & emptySquares;

        doublePawnMoves = ((pawns & Bitboard(0x000000000000FF00ULL)) << 8) & emptySquares;
        doublePawnMoves = (doublePawnMoves << 8) & emptySquares;

    } else {  // BLACK
        pawns = board.getBitboard(BLACK, PAWN);
        
        pawnMoves = (pawns >> 8) & emptySquares;

        doublePawnMoves = ((pawns & Bitboard(0x00FF000000000000ULL)) >> 8) & emptySquares;
        doublePawnMoves = (doublePawnMoves >> 8) & emptySquares;
    }

    while(pawnMoves) {
        int toSquare = pawnMoves.popLSB();
        int fromSquare = (color == WHITE) ? toSquare - 8 : toSquare + 8;
        
        Move move(toSquare, fromSquare, NORMAL);
        moveList.push_back(move);
    }

    while(doublePawnMoves) {
        int toSquare = doublePawnMoves.popLSB();
        int fromSquare = (color == WHITE) ? toSquare - 16 : toSquare + 16;
        
        Move move(toSquare, fromSquare, PAWN_DOUBLE_MOVE);
        moveList.push_back(move);
    }
}


std::vector<Move> Movegen::generateLegalMoves(Color color) {
    std::vector<Move> moveList;

    generatePawnMoves(color, moveList);

    return moveList;
}
