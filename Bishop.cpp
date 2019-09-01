// Charissa Zou
// czou9, ahu13, rmurato2
// Section 02

#include "Bishop.h"
using std::pair;


/* Defines the legal moves for Bishop
 * @param start the starting coordinates
 * @param end the ending coordinates
 * @return whether move is legal
 */
bool Bishop::legal_move_shape(pair<char, char> start, pair<char, char> end) const {
  int diff1 = (int)start.first - (int)end.first;
  int diff2 = (int)start.second - (int)end.second;
  if (diff1 !=0 && diff2 != 0){
    if ((diff1 * diff1) == (diff2 * diff2))
      return true;
  }
  return false;
}
