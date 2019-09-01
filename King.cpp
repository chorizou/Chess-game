//Rebecca Muratore
//rmurato2, ahu13, czou9

#include "King.h"
using std::pair;

/* Defines legal moves for King
 * @parma start the starting coordinates
 * @param end the ending coordinates
 * @return whether move is legal
 */
bool King::legal_move_shape(pair<char, char> start, pair<char, char> end) const {
  int char_diff = start.first - end.first;
  int num_diff = start.second - end.second;
  if (!(char_diff == 0 && num_diff == 0))
    if ((char_diff * char_diff <= 1) && (num_diff * num_diff <= 1))
	return true;
  return false;
}
