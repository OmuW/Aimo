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

Board::Board(std::string& fen) {
    for (int i = 0; i < PIECE_COUNT; ++i) {
        for (int j = 0; j < COLOR_COUNT; ++j) {
            board[j][i] = Bitboard(0);
        }
    }
    // first, we'll grab the piece positions
    std::string piecePlacement = fen.substr(0, fen.find(" "));
    // now, we'll iterate through the ranks
    int rank = 7;
    int file = 0;
    for (char c : piecePlacement) {
        if (c == '/') {
            rank--;
            file = 0;
        } else if (c >= '1' && c <= '8') {
            file += c - '0';
        } else {
            Color color = (c >= 'a' && c <= 'z') ? Color::BLACK : Color::WHITE;
            Piece piece;
            switch (c) {
                case 'p':
                case 'P':
                    piece = Piece::PAWN;
                    break;
                case 'n':
                case 'N':
                    piece = Piece::KNIGHT;
                    break;
                case 'b':
                case 'B':
                    piece = Piece::BISHOP;
                    break;
                case 'r':
                case 'R':
                    piece = Piece::ROOK;
                    break;
                case 'q':
                case 'Q':
                    piece = Piece::QUEEN;
                    break;
                case 'k':
                case 'K':
                    piece = Piece::KING;
                    break;
            }
            board[color][piece].setSquare(rank * 8 + file);
            file++;
        }
    }

    // now, we'll grab the active color
    std::string activeColorString = fen.substr(fen.find(" ") + 1, 1);
    activeColor = (activeColorString == "w") ? Color::WHITE : Color::BLACK;

    // now, we'll grab the castling rights
    std::string castlingRightsString = fen.substr(fen.find(" ") + 3, fen.find(" ", fen.find(" ") + 3) - (fen.find(" ") + 3));
    castlingRights = 0;
    if (castlingRightsString.find("K") != std::string::npos) {
        castlingRights |= CastlingRights::WHITE_KING_SIDE;
    }
    if (castlingRightsString.find("Q") != std::string::npos) {
        castlingRights |= CastlingRights::WHITE_QUEEN_SIDE;
    }
    if (castlingRightsString.find("k") != std::string::npos) {
        castlingRights |= CastlingRights::BLACK_KING_SIDE;
    }
    if (castlingRightsString.find("q") != std::string::npos) {
        castlingRights |= CastlingRights::BLACK_QUEEN_SIDE;
    }

    // now, we'll grab the en passant square
    std::string enPassantString = fen.substr(fen.find(" ", fen.find(" ") + 3) + 1, fen.find(" ", fen.find(" ", fen.find(" ") + 3) + 1) - (fen.find(" ", fen.find(" ") + 3) + 1));
    enPassant = Bitboard(0);
    if (enPassantString != "-") {
        int file = enPassantString[0] - 'a';
        int rank = enPassantString[1] - '1';
        enPassant.setSquare(rank * 8 + file);
    }

    // TODO: add halfmove clock and fullmove number
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