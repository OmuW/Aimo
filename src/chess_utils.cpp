#include "chess_utils.h"

namespace ChessUtils {
    std::string squareToString(int square) {
        std::string result = "";
        result += (char)('a' + (square % 8));
        result += (char)('1' + (square / 8));
        return result;
    }

    const Bitboard Files::A = Bitboard(0x0101010101010101ULL);
    const Bitboard Files::B = Bitboard(0x0202020202020202ULL);
    const Bitboard Files::C = Bitboard(0x0404040404040404ULL);
    const Bitboard Files::D = Bitboard(0x0808080808080808ULL);
    const Bitboard Files::E = Bitboard(0x1010101010101010ULL);
    const Bitboard Files::F = Bitboard(0x2020202020202020ULL);
    const Bitboard Files::G = Bitboard(0x4040404040404040ULL);
    const Bitboard Files::H = Bitboard(0x8080808080808080ULL);
}