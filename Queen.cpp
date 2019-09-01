// Anna Hu
// ahu13, czou9, rmurato2
// Section 02

#include "Queen.h"

/* Defines the legal moves for Queen
 * @param start: the starting coordinates
 * @param end: the ending coordinates
 * @return whether move is legal
 */
bool Queen::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const{
  int first_diff = start.first - end.first;
  int second_diff = start.second - end.second;
  if(!((start.first == end.first) && (start.second == end.second))){
    if((start.first == end.first) || (start.second == end.second)){
      return true;
    }
    if(first_diff * first_diff == second_diff * second_diff){
      return true;
    }
  }
  return false;
}
