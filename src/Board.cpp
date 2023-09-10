#include "Board.h"

std::array<std::array<std::string, PIECE_COUNT>, COLOR_COUNT> pieceStrings = {{
    {"P", "N", "B", "R", "Q", "K"},
    {"p", "n", "b", "r", "q", "k"}
}};

Board::Board() {
    board[WHITE][PAWN] = Bitboard(0x000000000000FF00ULL);
    board[WHITE][KNIGHT] = Bitboard(0x0000000000000042ULL);
    board[WHITE][BISHOP] = Bitboard(0x0000000000000024ULL);
    board[WHITE][ROOK] = Bitboard(0x0000000000000081ULL);
    board[WHITE][QUEEN] = Bitboard(0x0000000000000008ULL);
    board[WHITE][KING] = Bitboard(0x00000000000000010ULL);
    board[BLACK][PAWN] = Bitboard(0x00FF000000000000ULL);
    board[BLACK][KNIGHT] = Bitboard(0x4200000000000000ULL);
    board[BLACK][BISHOP] = Bitboard(0x2400000000000000ULL);
    board[BLACK][ROOK] = Bitboard(0x8100000000000000ULL);
    board[BLACK][QUEEN] = Bitboard(0x0800000000000000ULL);
    board[BLACK][KING] = Bitboard(0x1000000000000000ULL);
    activeColor = Color::WHITE;
    castlingRights = CastlingRights::WHITE_KING_SIDE
        | CastlingRights::WHITE_QUEEN_SIDE
        | CastlingRights::BLACK_KING_SIDE
        | CastlingRights::BLACK_QUEEN_SIDE;
    enPassant = Bitboard(0);
}

Bitboard Board::getBitboard(Piece piece, Color color) const {
    return board[piece][color];
}

void Board::setBitboard(Piece piece, Color color, const Bitboard& bitboard) {
    board[piece][color] = bitboard;
}

void Board::pprint() const {
    std::cout << "  |---|---|---|---|---|---|---|---|" << std::endl;
    for (int rank = 7; rank >= 0; --rank) {
        std::cout << rank + 1 << " ";
        for (int file = 0; file < 8; ++file) {
            int position = rank * 8 + file;
            bool found = false;
            for (int piece = 0; piece < PIECE_COUNT; ++piece) {
                for (int color = 0; color < COLOR_COUNT; ++color) {
                    if (board[color][piece].getSquare(position)) {
                        std::cout << "| " << pieceStrings[color][piece] << " ";
                        found = true;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
            if (!found) {
                std::cout << "|   ";
            }
        }
        std::cout << "|" << std::endl;
        std::cout << "  |---|---|---|---|---|---|---|---|" << std::endl;
    } 
    std::cout << "    a   b   c   d   e   f   g   h  " << std::endl;
    std::cout << std::endl;
    std::cout << "Active Color: " << (activeColor == WHITE ? "White" : "Black") << std::endl;
    std::cout << "Castling Rights: " << std::endl;
    std::cout << "    White King Side: " << ((castlingRights & WHITE_KING_SIDE) ? "Yes" : "No") << std::endl;
    std::cout << "    White Queen Side: " << ((castlingRights & WHITE_QUEEN_SIDE) ? "Yes" : "No") << std::endl;
    std::cout << "    Black King Side: " << ((castlingRights & BLACK_KING_SIDE) ? "Yes" : "No") << std::endl;
    std::cout << "    Black Queen Side: " << ((castlingRights & BLACK_QUEEN_SIDE) ? "Yes" : "No") << std::endl;
    std::string enPassantString = enPassant.countBits() ? ChessUtils::squareToString(enPassant.getLSB()) : "None";
    std::cout << "En Passant: " << enPassantString << std::endl;
}