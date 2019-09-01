// czou9, ahu13, rmurato2
// Section 02

#include "Chess.h"
#include "Board.h"
#include "Piece.h"
#include <utility>
#include <iostream>

using std::pair;
using std::map;
using std::iterator;


// Do not modify
/* Initializes the board with standard piece positions and set turn to white player
 */
Chess::Chess() : is_white_turn(true) {
  // Add the pawns
  for (int i = 0; i < 8; i++) {
    board.add_piece(std::pair<char, char>('A' + i, '1' + 1), 'P');
    board.add_piece(std::pair<char, char>('A' + i, '1' + 6), 'p');
  }

  // Add the rooks
  board.add_piece(std::pair<char, char>( 'A'+0 , '1'+0 ) , 'R' );
  board.add_piece(std::pair<char, char>( 'A'+7 , '1'+0 ) , 'R' );
  board.add_piece(std::pair<char, char>( 'A'+0 , '1'+7 ) , 'r' );
  board.add_piece(std::pair<char, char>( 'A'+7 , '1'+7 ) , 'r' );
  
  // Add the knights
  board.add_piece(std::pair<char, char>( 'A'+1 , '1'+0 ) , 'N' );
  board.add_piece(std::pair<char, char>( 'A'+6 , '1'+0 ) , 'N' );
  board.add_piece(std::pair<char, char>( 'A'+1 , '1'+7 ) , 'n' );
  board.add_piece(std::pair<char, char>( 'A'+6 , '1'+7 ) , 'n' );
  
  // Add the bishops
  board.add_piece(std::pair<char, char>( 'A'+2 , '1'+0 ) , 'B' );
  board.add_piece(std::pair<char, char>( 'A'+5 , '1'+0 ) , 'B' );
  board.add_piece(std::pair<char, char>( 'A'+2 , '1'+7 ) , 'b' );
  board.add_piece(std::pair<char, char>( 'A'+5 , '1'+7 ) , 'b' );
  
  // Add the kings and queens
  board.add_piece(std::pair<char, char>( 'A'+3 , '1'+0 ) , 'Q' );
  board.add_piece(std::pair<char, char>( 'A'+4 , '1'+0 ) , 'K' );
  board.add_piece(std::pair<char, char>( 'A'+3 , '1'+7 ) , 'q' );
  board.add_piece(std::pair<char, char>( 'A'+4 , '1'+7 ) , 'k' );
}


/* Moves a piece from start to end if valid
 * @param start the starting coordinate
 * @param end the ending coordinate to move to
 * @return whether move was successful
 */
bool Chess::make_move(std::pair<char, char> start, std::pair<char, char> end) {
  // make switch case for errors here
  switch(errors(start, end)){
  case 1: std::cerr << "Error: specified position not on board" << std::endl; return false;
  case 2: std::cerr << "Error: cannot move an empty space" << std::endl; return false;
  case 3: std::cerr << "Error: cannot move enemy's piece" << std::endl; return false;
  case 4: std::cerr << "Error: specified position is already occupied" << std::endl; return false;
  default: break;
  }

  // If its valid, either move or capture
  if ((board)(end) == NULL && (board)(start)->legal_move_shape(start, end)) {
    if (!board.obstruction(start, end)) {
      switch_pos(start, end, '-');
      if (in_check(is_white_turn)) {
	std::cerr << "Error: invalid move; can't put yourself in check" << std::endl;
	switch_pos(end, start, '-');
	return false;
      }
      piece_promotion(end, (board)(end)->to_ascii());
      is_white_turn = !is_white_turn;
      return true;
    }
    std::cerr << "Error: path obstructed; cannot move to specified position" << std::endl;
    return false;
  } else if ((board)(end) != NULL && (board)(start)->legal_capture_shape(start, end)) {
    if (!board.obstruction(start, end)) {
      char p = switch_pos(start, end, '-');
      if (in_check(is_white_turn)) {
	std::cerr << "Error: invalid move; can't put yourself in check" << std::endl;
	switch_pos(end, start, p);
	return false;
      }
      piece_promotion(end, (board)(end)->to_ascii());
      is_white_turn = !is_white_turn;
      return true;
    }
    std::cerr << "Error: path obstructed; cannot move to specified position" << std::endl;
    return false;
  }
  
  std::cerr << "Error: not legal move or capture shape" << std::endl;
  return false;
}


/* Turns a pawn into a Queen if it reaches end of enemy line
 * @param pos position the pawn is in
 * @param piece designator piece type
 * @return whether promotion succeeds
 */
bool Chess::piece_promotion(pair<char, char> pos, char piece_designator) {
  if (piece_designator == 'P' && pos.second == '8') {
    board.remove_piece(pos);
    board.add_piece(pos, 'Q');
    return true;
  } else if (piece_designator == 'p' && pos.second == '1') {
    board.remove_piece(pos);
    board.add_piece(pos, 'q');
    return true;
  }
  return false;
}


/* Checks if current player is in check (i.e. one move by enemy player can capture
 * their king
 * @param white color of current player
 * @return whether player is in check
 */
bool Chess::in_check(bool white) const {
  std::vector<pair<char, char>> vec = board.occ_pos();
  pair<char, char> k_pos;

  // Finds position of king
  if (white)
    k_pos = board.find_piece('K');
  else
    k_pos = board.find_piece('k');

  // Loop thru every enemy piece and see if they can capture the king if one move
  for (size_t i = 0; i < vec.size(); i++) {
    if ((board)(vec[i])->is_white() != white)
      if ((board)(vec[i])->legal_capture_shape(vec[i], k_pos))
	if (!board.obstruction(vec[i], k_pos))
	  return true;
  }  
  return false;
}


/* Checks if current player is in a checkmate position
 * @param white which player's turn it is
 * @return whether this is a checkmate position 
 */
bool Chess::in_mate(bool white) {
  if (in_check(white))
    if (!pos_moves(white))
      return true;
  return false;
}


/* Checks if the players are in a stalemate
 * @param white the player's turn
 * @return whether it's a stalemate
 */
bool Chess::in_stalemate(bool white) {
  if (!in_check(white))
    if (!pos_moves(white))
      return true;
  return false;
}


/* Checks for different error conditions
 * @return the error
 */
int Chess::errors(pair<char, char> start, pair<char, char> end) {
  // Checks if both positions are valid
  if (!(board.on_board(start)) || !(board.on_board(end)))
    return 1;
  else if ((board)(start) == NULL)
    return 2;
  // Cannot move enemy's piece or move to a place already occupied by own piece
  if ((board)(start)->is_white() != turn_white())
    return 3;
  else if (board(end) != NULL && (board(end))->is_white() == turn_white())
    return 4;
  return 0;
}


/* Switches the position of the pieces on the locations specified if they exist;
 * if not, move piece on start to end and place the specificed piece in start
 */
char Chess::switch_pos(pair<char, char> start, pair<char, char> end, char p) {
  char p1 = (board)(start)->to_ascii(); char p2;
  if ((board)(end) != NULL) {
    p2 = (board)(end)->to_ascii();
    board.remove_piece(end);
  } else
    p2 = '-';
  board.add_piece(end, p1);
  board.remove_piece(start);
  if (p != '-')
    board.add_piece(start, p);
  return p2;
}


/* Checks if there are any moves left for player to get out of check
 * @param white which player's turn it is
 * @return whether there are moves left
 */
bool Chess::pos_moves(bool white) {
  std::vector<pair<char, char>> vec = board.occ_pos();
  for (size_t i = 0; i < vec.size(); i++) {
    for (char r = '8'; r >= '1'; r--) {
      for (char c = 'A'; c <= 'H'; c++) {
	pair<char, char> cur = std::make_pair(c, r);
	if (errors(vec[i], cur) != 0)
	  continue;
	if ((board)(cur) == NULL && (board)(vec[i])->legal_move_shape(vec[i], cur)) {
	  if (!board.obstruction(vec[i], cur)) {
	    switch_pos(vec[i], cur, '-');
	    if (!in_check(white)) {
	      switch_pos(cur, vec[i], '-');
	      return true;
	    }
	    switch_pos(cur, vec[i], '-');
	  }
	} else if ((board)(cur) != NULL && (board)(vec[i])->legal_capture_shape(vec[i], cur)) {
	  if (!board.obstruction(vec[i], cur)) {
	    char p = switch_pos(vec[i], cur, '-');
	    if (!in_check(white)) {
	      //std::cout << "Can move " << (board)(cur)->to_ascii() << " from  " <<
	      //vec[i].first << vec[i].second << " to " << c << r << std::endl;
	      switch_pos(cur, vec[i], p);
	      return true;
	    }
	    //std::cout << "CANNOT move " << (board)(cur)->to_ascii() << " from  " <<
	    //vec[i].first << vec[i].second << " to " << c << r << std::endl;
	    switch_pos(cur, vec[i], p);
	  }
	}
      }
    }
  }
  return false;
}


/* Given position and piece, places it on the board */
void Chess::set_board(pair<char, char> pos, char piece_designator) {
  board.add_piece(pos, piece_designator);
}


/* Sets the player's turn */
bool Chess::set_turn(char turn) {
  is_white_turn = (turn == 'w') ? true : false;
  return true;
}

/* Clears the entire board */
bool Chess::clear_board() {
  std::vector<pair<char, char>> vec = board.occ_pos();
  for (size_t i = 0; i < vec.size(); i++)
    board.remove_piece(vec[i]);
  return true;
}


/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
std::ostream& operator<< (std::ostream& os, const Chess& chess) {
  // Write the board out and then either the character 'w' or the character 'b',
  // depending on whose turn it is
  return os << chess.get_board() << (chess.turn_white() ? 'w' : 'b');
}


/* Reads in a board from a file and sets current board to match it */
std::istream& operator>> (std::istream& is, Chess& chess) {
  chess.clear_board();
  char cur;
  for (char r = '8'; r >= '1'; r--)
    for (char c = 'A'; c <= 'H'; c++) {
      pair<char, char> temp = std::make_pair(c, r);
      is >> cur;
      if (cur == '-')
	continue;
      chess.set_board(temp, cur);
    }
  is >> cur;
  chess.set_turn(cur);
  return is;
}
