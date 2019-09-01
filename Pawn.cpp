// Charissa Zou
// czou9, ahu13, rmurato2
// Section 02

#include "Pawn.h"
using std::pair;


/* Defines the legal moves for a pawn object
 * @param start the starting coordinates
 * @param end the ending coordinates
 * @return whether move is legal
 */
bool Pawn::legal_move_shape(pair<char, char> start, pair<char, char> end) const {
  if (to_ascii() == 'P')
    return white_move(start, end);
  else
    return black_move(start, end);
}


/* legal moves for white pawn */
bool Pawn::white_move(pair<char, char> start, pair<char, char> end) const {
  if (start.second == '2') {
    if ((end.first == start.first) && (end.second != start.second)
	&& (end.second - start.second <= 2))
      return true;
  } else {
    if ((end.first == start.first) && (end.second - start.second == 1))
      return true;
  }
  return false;
}


/* legal moves for black pawn */
bool Pawn::black_move(pair<char, char> start, pair<char, char> end) const {
  if (start.second == '7') {
    if ((end.first == start.first) && (end.second != start.second)
	&& (start.second - end.second <= 2))
      return true;
  } else {
    if ((end.first == start.first) && (start.second - end.second == 1))
      return true;
  }
  return false;
}


/* Defines legal move for pawns to capture: front diagonal
 * @param start the starting coordinates
 * @param end the ending coordinates
 * @return whether move is legal
 */
bool Pawn::legal_capture_shape(pair<char, char> start, pair<char, char> end) const {
  int char_diff = end.first - start.first;
  int num_diff = end.second - start.second;
  if (to_ascii() == 'P') {
    if ((num_diff == 1) && (char_diff * char_diff == 1))
      return true;
  } else {
    if ((num_diff == -1) && (char_diff * char_diff == 1))
      return true;
  } 
  return false;
}
