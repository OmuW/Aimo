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

int Move::getTo() const {
    return to;
}

int Move::getFrom() const {
    return from;
}

void Move::setPromotionPiece(Piece piece) {
    promotionPiece = piece;
}

void Move::setCapturedPiece(Piece piece) {
    capturedPiece = piece;
}

MoveType Move::getMoveType() const {
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
    boardPieceArray = {{
        "r", "n", "b", "q", "k", "b", "n", "r",
        "p", "p", "p", "p", "p", "p", "p", "p",
        "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "P", "P", "P", "P", "P", "P", "P", "P",
        "R", "N", "B", "Q", "K", "B", "N", "R"
    }};

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
            boardPieceArray[rank * 8 + file] = pieceStrings[color][piece];
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

Piece Board::getPiece(int position) const {
    std::string pieceString = boardPieceArray[position];
    if (pieceString == "P" || pieceString == "p") {
        return PAWN;
    } else if (pieceString == "N" || pieceString == "n") {
        return KNIGHT;
    } else if (pieceString == "B" || pieceString == "b") {
        return BISHOP;
    } else if (pieceString == "R" || pieceString == "r") {
        return ROOK;
    } else if (pieceString == "Q" || pieceString == "q") {
        return QUEEN;
    } else if (pieceString == "K" || pieceString == "k") {
        return KING;
    } else {
        std::cout << "unknown piece at position " << position << ": " << pieceString << std::endl;
        return PIECE_COUNT;
    }
}

void Board::movePieceInBitboard(Color color, Piece piece, int from, int to) {
    board[color][piece].clearSquare(from);
    board[color][piece].setSquare(to);
    boardPieceArray[from] = "";
    boardPieceArray[to] = pieceStrings[color][piece];
    occupiedSquares.setSquare(to);
    occupiedSquares.clearSquare(from);
    emptySquares.clearSquare(to);
    emptySquares.setSquare(from);
    if (color == WHITE) {
        whitePieces.setSquare(to);
        whitePieces.clearSquare(from);
    } else {
        blackPieces.setSquare(to);
        blackPieces.clearSquare(from);
    }
}

void Board::removePieceFromBitboard(Color color, Piece piece, int square) {
    board[color][piece].clearSquare(square);
    boardPieceArray[square] = "";
    occupiedSquares.clearSquare(square);
    emptySquares.setSquare(square);
    if (color == WHITE) {
        whitePieces.clearSquare(square);
    } else {
        blackPieces.clearSquare(square);
    }
}

Bitboard Board::getBitboard(Color color, Piece piece) const {
    return board[color][piece];
}

void Board::setBitboard(Color color, Piece piece, const Bitboard& bitboard) {
    board[color][piece] = bitboard;
}

std::string Board::getPieceString(int position) const {
    return boardPieceArray[position];
}

void Board::setPieceString(int position, std::string pieceString) {
    boardPieceArray[position] = pieceString;
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

Color Board::getActiveColor() const {
    return activeColor;
}


void printArr(std::array<std::string, 64> arr) {
    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            int position = rank * 8 + file;
            std::cout << (arr[position] != "" ? arr[position] : " ") << " ";
        }
        std::cout << std::endl;
    }
}



void Board::makeMove(const Move& move) {
    if (enPassant) {
        enPassant = Bitboard(0);
    }
    int from = move.getFrom();
    int to = move.getTo();

    MoveType moveType = move.getMoveType();

    // Identify the moving piece
    Piece movingPiece = getPiece(from);

    printArr(boardPieceArray);

    if (moveType == CAPTURE) {
        Piece capturedPiece = getPiece(to);
        removePieceFromBitboard(activeColor == WHITE ? BLACK : WHITE, capturedPiece, to);
    }

    // Update the board bitboards
    movePieceInBitboard(activeColor, movingPiece, from, to);

    // Handle special move cases
    switch(moveType) {
        case NORMAL: {
            // Nothing extra for normal moves
            break;
        }
        case PAWN_DOUBLE_MOVE: {
            // Maybe set an en passant square?
            if (activeColor == WHITE) {
                enPassant = Bitboard(1ULL << (to - 8));
            } else {
                enPassant = Bitboard(1ULL << (to + 8));
            }
            break;
        }
        case CAPTURE: {
            break;
        }
        case EN_PASSANT: {
            // Remove the captured pawn
            Color capturedColor = activeColor == WHITE ? BLACK : WHITE;
            int epSquare = activeColor == WHITE ? to - 8 : to + 8;
            removePieceFromBitboard(capturedColor, PAWN, epSquare);
            break;
        }
        case CASTLING: {
            break;
        }
        case PROMOTION: {
            break;
        }
    }

    lastMove = move;
    activeColor = activeColor == WHITE ? BLACK : WHITE;
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

