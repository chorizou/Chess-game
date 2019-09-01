// Anna Hu
// ahu13, czou9, rmurato2
// Section 02

#include "Knight.h"

/* Defines the legal moves for Knight
 * @param start: the starting coordinates
 * @param end: the ending coordinates
 * @return whether move is legal
 */
bool Knight::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  int second_diff = start.second - end.second;
  int first_diff = start.first - end.first;
  if(second_diff * second_diff == 4){
    if(first_diff * first_diff == 1){
      return true;
    }
  }
  if(second_diff * second_diff == 1){
    if(first_diff * first_diff == 4){
      return true;
    }
  }
  return false;    
}
