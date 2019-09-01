#ifndef CHESS_H
#define CHESS_H

#include <iostream>
#include "Piece.h"
#include "Board.h"

class Chess {

public:
  // This default constructor initializes a board with the standard
  // piece positions, and sets the state to white's turn
  Chess();

  // Returns a constant reference to the board 
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  const Board& get_board() const { return board; }
  
  // Returns true if it is white's turn
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  bool turn_white() const { return is_white_turn; }

  // Attemps to make a move. If successful, the move is made and
  // the turn is switched white <-> black
  bool make_move(std::pair<char, char> start, std::pair<char, char> end);

  // Promotes pawn to queen if at end of enemy line
  bool piece_promotion(std::pair<char, char> pos, char piece_designator);

  // Returns true if the designated player is in check
  bool in_check(bool white) const;

  // Returns true if the designated player is in mate
  bool in_mate(bool white);

  // Returns true if the designated player is in mate
  bool in_stalemate(bool white);

  // Checks for error conditions for start and end positions
  int errors(std::pair<char, char> start, std::pair<char, char> end);

  // Switches the pieces at two positions
  char switch_pos(std::pair<char, char> start, std::pair<char, char> end, char p);

  // Checks if there are any possible moves left
  bool pos_moves(bool white);

  // Sets a piece at a specific place on the board
  void set_board(std::pair<char, char> pos, char piece_designator);

  // Sets the turn for the player
  bool set_turn(char turn);
  
  // Clears the entire board
  bool clear_board();

private:
  // The board
  Board board;

  // Is it white's turn?
  bool is_white_turn;

};

// Writes the board out to a stream
std::ostream& operator<< (std::ostream& os, const Chess& chess);

// Reads the board in from a stream
std::istream& operator>> (std::istream& is, Chess& chess);


#endif // CHESS_H
