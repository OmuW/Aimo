#include "Movegen.h"

void Movegen::generatePawnMoves(std::vector<Move>& moveList) {
    Bitboard pawns;
    Bitboard emptySquares = board.getEmptySquares();
    Bitboard pawnMoves, doublePawnMoves, pawnAttacksLeft, pawnAttacksRight, enPassantLeft, enPassantRight;
    Color color = board.getActiveColor();

    if(color == WHITE) {
        pawns = board.getBitboard(WHITE, PAWN);
        
        pawnMoves = (pawns << 8) & emptySquares;

        doublePawnMoves = ((pawns & Bitboard(0x000000000000FF00ULL)) << 8) & emptySquares;
        doublePawnMoves = (doublePawnMoves << 8) & emptySquares;

        pawnAttacksLeft = ((pawns & ~ChessUtils::Files::A) << 7) & board.getBlackPieces();
        pawnAttacksRight = ((pawns & ~ChessUtils::Files::H) << 9) & board.getBlackPieces();

        // need to handle en passant
        enPassantLeft = ((pawns & ~ChessUtils::Files::A) << 7) & board.getEnPassant();
        enPassantRight = ((pawns & ~ChessUtils::Files::H) << 9) & board.getEnPassant();

    } else {  // BLACK
        pawns = board.getBitboard(BLACK, PAWN);
        
        pawnMoves = (pawns >> 8) & emptySquares;

        doublePawnMoves = ((pawns & Bitboard(0x00FF000000000000ULL)) >> 8) & emptySquares;
        doublePawnMoves = (doublePawnMoves >> 8) & emptySquares;

        pawnAttacksLeft = ((pawns & ~ChessUtils::Files::A) >> 9) & board.getWhitePieces();
        pawnAttacksRight = ((pawns & ~ChessUtils::Files::H) >> 7) & board.getWhitePieces();

        enPassantLeft = ((pawns & ~ChessUtils::Files::A) >> 9) & board.getEnPassant();
        enPassantRight = ((pawns & ~ChessUtils::Files::H) >> 7) & board.getEnPassant();
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

    while(pawnAttacksLeft) {
        int toSquare = pawnAttacksLeft.popLSB();
        int fromSquare = (color == WHITE) ? toSquare - 7 : toSquare + 9;
        
        Move move(toSquare, fromSquare, CAPTURE);
        moveList.push_back(move);
    }

    while(pawnAttacksRight) {
        int toSquare = pawnAttacksRight.popLSB();
        int fromSquare = (color == WHITE) ? toSquare - 9 : toSquare + 7;

        Move move(toSquare, fromSquare, CAPTURE);
        moveList.push_back(move);
    }

    while(enPassantLeft) {
        int toSquare = enPassantLeft.popLSB();
        int fromSquare = (color == WHITE) ? toSquare - 7 : toSquare + 9;

        Move move(toSquare, fromSquare, EN_PASSANT);
        moveList.push_back(move);
    }

    while(enPassantRight) {
        int toSquare = enPassantRight.popLSB();
        int fromSquare = (color == WHITE) ? toSquare - 9 : toSquare + 7;

        Move move(toSquare, fromSquare, EN_PASSANT);
        moveList.push_back(move);
    }
}


std::vector<Move> Movegen::generateLegalMoves() {
    std::vector<Move> moveList;
    /* THIS IS ONLY FOR NOW, ONLY FOR PAWNS, WE NEED A BETTER WAY TO DO THIS!!!!!*/
    /* TODO: */
    if ((board.getBitboard(WHITE, PAWN) & Bitboard(0xFF00000000000000ULL)) 
        || (board.getBitboard(BLACK, PAWN) & Bitboard(0x00000000000000FFULL))) {
        return moveList;
    }
    generatePawnMoves(moveList);

    return moveList;
}
