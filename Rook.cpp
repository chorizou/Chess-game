//Rebecca Muratore
///rmurato2, ahu13, czou9

#include "Rook.h"

/* Defines legal moves for Rook
 * @param start the starting coordinates
 * @param end the ending coordinates
 * @return whether move is legal
 */
bool Rook::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  if(!((start.first) - (end.first) == 0 && (start.second) - (end.second) == 0))
    if((start.first) - (end.first) == 0 || (start.second) - (end.second) == 0)
      return true;
  return false;  
}

