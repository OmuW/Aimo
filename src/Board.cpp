#include "Board.h"

std::array<std::array<std::string, PIECE_COUNT>, COLOR_COUNT> pieceStrings = {{
    {"P", "N", "B", "R", "Q", "K"},
    {"p", "n", "b", "r", "q", "k"}
}};

Move::Move() {
    to = 0;
    from = 0;
    moveType = MoveType::NORMAL;
    promotionPiece = PIECE_COUNT;
    capturedPiece = PIECE_COUNT;
}

Move::Move(int toSquare, int fromSquare, MoveType move) {
    to = toSquare;
    from = fromSquare;
    moveType = move;
    promotionPiece = PIECE_COUNT;
    capturedPiece = PIECE_COUNT;
}

void Move::setPromotionPiece(Piece piece) {
    promotionPiece = piece;
}

void Move::setCapturedPiece(Piece piece) {
    capturedPiece = piece;
}

MoveType Move::getMoveType() {
    return moveType;
}

Piece Move::getPromotionPiece() {
    return promotionPiece;
}

Piece Move::getCapturedPiece() {
    return capturedPiece;
}

void Move::pprint() const {
    std::cout << "Move: " << ChessUtils::squareToString(from) << " -> " << ChessUtils::squareToString(to) << std::endl;
}

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

    occupiedSquares = board[WHITE][PAWN]
        | board[WHITE][KNIGHT]
        | board[WHITE][BISHOP]
        | board[WHITE][ROOK]
        | board[WHITE][QUEEN]
        | board[WHITE][KING]
        | board[BLACK][PAWN]
        | board[BLACK][KNIGHT]
        | board[BLACK][BISHOP]
        | board[BLACK][ROOK]
        | board[BLACK][QUEEN]
        | board[BLACK][KING];
    
    emptySquares = ~occupiedSquares;

    activeColor = Color::WHITE;
    castlingRights = CastlingRights::WHITE_KING_SIDE
        | CastlingRights::WHITE_QUEEN_SIDE
        | CastlingRights::BLACK_KING_SIDE
        | CastlingRights::BLACK_QUEEN_SIDE;
    enPassant = Bitboard(0);
    halfMoveClock = 0;
    fullMoveNumber = 1;
    lastMove = Move(0, 0, MoveType::NORMAL);
}

Board::Board(std::string& fen) {
    for (int i = 0; i < PIECE_COUNT; ++i) {
        for (int j = 0; j < COLOR_COUNT; ++j) {
            board[j][i] = Bitboard(0);
        }
    }

    std::istringstream fenStream(fen);
    std::string segment;

    // first, we'll grab the piece positions
    std::getline(fenStream, segment, ' ');
    int rank = 7;
    int file = 0;
    for (char c : segment) {
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

    occupiedSquares = board[WHITE][PAWN]
        | board[WHITE][KNIGHT]
        | board[WHITE][BISHOP]
        | board[WHITE][ROOK]
        | board[WHITE][QUEEN]
        | board[WHITE][KING]
        | board[BLACK][PAWN]
        | board[BLACK][KNIGHT]
        | board[BLACK][BISHOP]
        | board[BLACK][ROOK]
        | board[BLACK][QUEEN]
        | board[BLACK][KING];
    
    whitePieces = board[WHITE][PAWN]
        | board[WHITE][KNIGHT]
        | board[WHITE][BISHOP]
        | board[WHITE][ROOK]
        | board[WHITE][QUEEN]
        | board[WHITE][KING];
    
    blackPieces = board[BLACK][PAWN]
        | board[BLACK][KNIGHT]
        | board[BLACK][BISHOP]
        | board[BLACK][ROOK]
        | board[BLACK][QUEEN]
        | board[BLACK][KING];

    emptySquares = ~occupiedSquares;

    // now, we'll grab the active color
    std::getline(fenStream, segment, ' ');
    activeColor = (segment == "w") ? Color::WHITE : Color::BLACK;

    // now, we'll grab the castling rights
    std::getline(fenStream, segment, ' ');
    castlingRights = 0;
    if (segment.find("K") != std::string::npos) {
        castlingRights |= CastlingRights::WHITE_KING_SIDE;
    }
    if (segment.find("Q") != std::string::npos) {
        castlingRights |= CastlingRights::WHITE_QUEEN_SIDE;
    }
    if (segment.find("k") != std::string::npos) {
        castlingRights |= CastlingRights::BLACK_KING_SIDE;
    }
    if (segment.find("q") != std::string::npos) {
        castlingRights |= CastlingRights::BLACK_QUEEN_SIDE;
    }

    // now, we'll grab the en passant square
    std::getline(fenStream, segment, ' ');
    enPassant = Bitboard(0);
    if (segment != "-") {
        int file = segment[0] - 'a';
        int rank = segment[1] - '1';
        enPassant.setSquare(rank * 8 + file);
    }

    // now, we'll grab the half move clock
    std::getline(fenStream, segment, ' ');
    halfMoveClock = std::stoi(segment);

    // now, we'll grab the full move number
    std::getline(fenStream, segment, ' ');
    fullMoveNumber = std::stoi(segment);

    lastMove = Move(0, 0, MoveType::NORMAL);
}

Bitboard Board::getBitboard(Color color, Piece piece) const {
    return board[color][piece];
}

void Board::setBitboard(Color color, Piece piece, const Bitboard& bitboard) {
    board[color][piece] = bitboard;
}

Bitboard Board::getOccupiedSquares() const {
    return occupiedSquares;
}

Bitboard Board::getEmptySquares() const {
    return emptySquares;
}

Bitboard Board::getWhitePieces() const {
    return whitePieces;
}

Bitboard Board::getBlackPieces() const {
    return blackPieces;
}

Bitboard Board::getEnPassant() const {
    return enPassant;
}

void Board::setOccupiedSquares(const Bitboard& bitboard) {
    occupiedSquares = bitboard;
}

void Board::setEmptySquares(const Bitboard& bitboard) {
    emptySquares = bitboard;
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
    std::cout << "Half Move Clock: " << halfMoveClock << std::endl;
    std::cout << "Full Move Number: " << fullMoveNumber << std::endl;
}