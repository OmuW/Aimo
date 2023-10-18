#include "Evaluation.h"
#include "Board.h"
#include "Bitboard.h"

int _evaluate_pawns(const Board& board) {
  int score = 0;
  // count white pawns
  Bitboard white_pawns = board.getBitboard(WHITE, PAWN);
  score += white_pawns.countBits();

  // count black pawns
  Bitboard black_pawns = board.getBitboard(BLACK, PAWN);
  score -= black_pawns.countBits();

  // if white pawn on 8th rank, add 9999 points
  if (white_pawns & Bitboard(0xFF00000000000000)) {
    score += 9999;
  }
  if (black_pawns & Bitboard(0x00000000000000FF)) {
    score -= 9999;
  }

  return score;
}

int evaluate(const Board& board) {
  int score = 0;
  score += _evaluate_pawns(board);
  return score;
}