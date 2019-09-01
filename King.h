#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {

public:
  bool legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const override;

  char to_ascii() const { return is_white() ? 'K' : 'k'; }

private:
  // Do not modify
  King(bool is_white) : Piece(is_white) {}

  friend Piece* create_piece(char piece_designator);
};

#endif // KING_H
