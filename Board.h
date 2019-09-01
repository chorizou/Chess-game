#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include <vector>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Mystery.h"


class Board {

  // Throughout, we will be accessing board positions using an std::pair<char, char>.
  // The assumption is that the first value is the column with values in
  // {'A','B','C','D','E','F','G','H'} (all caps)
  // and the second is the row, with values in {'1','2','3','4','5','6','7','8'}

public:
  // Default constructor
  Board();

  // Destrutor to free memory
  ~Board();

  // Returns a const pointer to the piece at a prescribed location if it exists,
  // or nullptr if there is nothing there.
  const Piece* operator() (std::pair<char, char> position) const;

  // Checks if piece is valid
  bool valid_piece(char piece_designator);

  // Attempts to add a new piece with the specified designator, at the given location.
  // Returns false if:
  // -- the designator is invalid,
  // -- the specified location is not on the board, or
  // -- if the specified location is occupied
  bool add_piece(std::pair<char, char> position, char piece_designator);

  // Removes a piece from specified location if it exists
  bool remove_piece(std::pair<char, char> position);

  // Finds position of specified piece
  std::pair<char, char> find_piece(char piece_designator) const;

  // Checks if specified position is located on board
  bool on_board(std::pair<char, char> position) const;

  // Returns a list of occupied positions
  std::vector<std::pair<char, char>> occ_pos() const;

  // Returns true if the board has the right number of kings on it
  bool has_valid_kings() const;
  
  // Checks if there are any pieces between start and end positions for a specific
  // pieces's valid move or capture
  bool obstruction(std::pair<char, char> start, std::pair<char, char> end) const;

  // Checks for obstruction for Bishop
  bool obs_B(std::pair<char, char> start, std::pair<char, char> end) const;

  // Checks for obstruction for Rook
  bool obs_R(std::pair<char, char> start, std::pair<char, char> end) const;

  // Checks for obstruction for Queen
  bool obs_Q(std::pair<char, char> start, std::pair<char, char> end) const;

  // Checks for obstruction for Pawn, white
  bool obs_P(std::pair<char, char> start, std::pair<char, char> end) const;

  // Checks for obstruction for pawn, black
  bool obs_p(std::pair<char, char> start, std::pair<char, char> end) const;

  // Checks for obstruction for the mystery piece
  bool obs_M(std::pair<char, char> start, std::pair<char, char> end) const;

  // Sets the background color at a position on the board
  void set_bg(char r, char c) const;

  // Displays the board by printing it to stdout
  void display() const;

private:
  // The sparse map storing the pieces, keyed off locations
  std::map<std::pair<char, char>, Piece*> occ;
};

// Write the board state to an output stream
std::ostream& operator<< (std::ostream& os, const Board& board);


#endif // BOARD_H
