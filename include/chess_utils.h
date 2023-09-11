#ifndef CHESS_UTILS_H
#define CHESS_UTILS_H
#include <string>
#include "Bitboard.h"

namespace ChessUtils {
  std::string squareToString(int square);
  extern struct Files {
    static const Bitboard A;
    static const Bitboard B;
    static const Bitboard C;
    static const Bitboard D;
    static const Bitboard E;
    static const Bitboard F;
    static const Bitboard G;
    static const Bitboard H;
  } Files;
}
#endif