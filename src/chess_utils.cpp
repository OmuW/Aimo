#include "chess_utils.h"

namespace ChessUtils {
    std::string squareToString(int square) {
        std::string result = "";
        result += (char)('a' + (square % 8));
        result += (char)('1' + (square / 8));
        return result;
    }
}