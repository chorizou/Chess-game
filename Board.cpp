// czou9, ahu13, rmurato2
// Section 02

#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include "Piece.h"
#include "Board.h"
#include "CreatePiece.h"
#include "Terminal.h"

using std::vector;
using std::pair;
using std::map;
using std::iterator;


/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
Board::Board(){}

/* Destructor */
Board::~Board() {
  for (map<pair<char, char>, Piece*>::iterator it = occ.begin();
       it != occ.end();
       ++it)
    delete it->second;
}


/* Determines whether specified space is occupied
 * @param position position to check
 * @return the piece occupying the space or null if space is empty
 */
const Piece* Board::operator()(pair<char, char> position) const {
  for (map<pair<char, char>, Piece*>::const_iterator it = occ.begin();
       it != occ.end();
       ++it) {
    if ((it->first).first == position.first && (it->first).second == position.second)
      return it->second;
  }
  return NULL;
}


/* Checks if the piece designator denotes a valid piece*/
bool Board::valid_piece(char piece_designator) {
  switch (piece_designator) {
  case 'K': case 'k': case 'Q': case 'q': case 'B': case 'b': 
  case 'N': case 'n': case 'R': case 'r': case 'P': case 'p': 
  case 'M': case 'm': return true;
  default: return false;
  }
}


/* Adds specified piece to specified position if piece and position both exist
 * @parma position location to add piece
 * @param piece_designator type of piece
 * @return whether add was successful
 */
bool Board::add_piece(pair<char, char> position, char piece_designator) {
  if (!valid_piece(piece_designator))
    return false;  
  if (on_board(position)) {
    if ( (*this)(position) == NULL) {
      occ[position] = create_piece(piece_designator);
      return true;
    }
  }
  return false;
}


/* Removes the piece at the specified position
 * @param position position to remove piece
 * @return whether removal was successful
 */
bool Board::remove_piece(pair<char, char> position) {
  if (occ.find(position) != occ.end()) {
    delete occ[position];
    occ.erase(position);
    return true;
  }
  return false;
}


/* Finds position of specified piece
 * @param piece_designator the piece to find
 * @return position of piece
 */
pair<char, char> Board::find_piece(char piece_designator) const {
  for (map<pair<char, char>, Piece*>::const_iterator it = occ.begin();
       it != occ.end();
       ++it) {
    if ((it->second)->to_ascii() == piece_designator)
      return it->first;
  }
  return std::make_pair(NULL, NULL);
}


/* Checks if specificed location is valid */
bool Board::on_board(pair<char, char> position) const {
  if (position.first < 'A' || position.first > 'H' ||
      position.second < '1' || position.second > '8')
      return false;
  return true;
}


/* Returns a list of occupied positions
 * @return the list of positions
 */
vector<pair<char, char>> Board::occ_pos() const {
  vector<pair<char, char>> v;
  for (map<pair<char, char>, Piece*>::const_iterator it = occ.begin();
       it != occ.end();
       ++it)
    v.push_back(it->first);
  return v;
}


/* Checks if there are a valid number of kings on the board
 * @return whether number of kings are valid (i.e. = 2)
 */
bool Board::has_valid_kings() const {
  int wk = 0;
  int bk = 0;
  for (map<pair<char, char>, Piece*>::const_iterator it = occ.begin();
       it != occ.end();
       ++it) {
    if ((*(it->second)).to_ascii() == 'K')
      wk++;
    else if ((*(it->second)).to_ascii() == 'k')
      bk++;
  }
  if (wk && bk)
    return true;
  return false;
}


/* helper function- checks if any pieces are between start and end, dependent on piece
 * @param start- starting coordinate
 * @param end- ending coordinate
 * @return whether there is a piece between start and end
 */
bool Board::obstruction(pair<char, char> start, pair<char, char> end) const {
  if ((*this)(start) == NULL) {
    std::cerr << "Error: empty starting position" << std::endl;
    return true;
  }
  switch((*this)(start)->to_ascii()) {
  case 'B': case 'b': return obs_B(start, end);
  case 'R': case 'r': return obs_R(start, end);
  case 'Q': case 'q': return obs_Q(start, end);
  case 'P': return obs_P(start, end);
  case 'p': return obs_p(start, end);
  case 'M': case 'm': return obs_M(start, end);
  default: return false;
  }
}


/* Checks for obstruction for Bishop
 */
bool Board::obs_B(pair<char, char> start, pair<char, char> end) const {
  char sf = start.first; char ss = start.second;
  char ef = end.first; char es = end.second;
  char c = ss;

  //if up-right movement
  if (sf < ef && ss < es) {
    c = ss + 1;
    for (char r = sf + 1; r <= ef - 1; r++) {
      if ((*this)(std::make_pair(r, c)) != NULL)
	return true;
      c++;
    }
  }
  //if down-left movement
  else if (sf > ef && ss > es) {
    c = ss - 1;
    for (char r = sf - 1; r >= ef + 1; r--) {
      if ((*this)(std::make_pair(r, c)) != NULL)
	return true;
      c--;
    }
  }
  //if down-right movement
  else if (sf < ef && ss > es) {
    c = ss - 1;
    for (char r = sf + 1; r <= ef - 1; r++) {
      if ((*this)(std::make_pair(r, c)) != NULL)
	return true;
      c--;
    }
  }
  //if up-left movement
  else if (sf > ef && ss < es) {
    c = ss + 1;
    for (char r = sf - 1; r >= ef + 1; r--) {
      if ((*this)(std::make_pair(r, c)) != NULL)
	return true;
      c++;
    }
  }
  return false;
}


/* Checks for obstruction for Rook
 */
bool Board::obs_R(pair<char, char> start, pair<char, char> end) const {
  char sf = start.first; char ss = start.second;
  char ef = end.first; char es = end.second;

  if(sf < ef && ss == es){
    for(char r = sf + 1; r <= ef - 1; r++) {
      if((*this)(std::make_pair(r, ss)) != NULL)
        return true;
    }
  } else if(sf > ef && ss == es){
    for(char r = sf - 1; r >= ef + 1; r--) {
      if((*this)(std::make_pair(r, ss)) != NULL)
        return true;
    }
  } else if(sf == ef && ss < es){
    for(char c = ss + 1; c <= es - 1; c++) {
      if((*this)(std::make_pair(sf, c)) != NULL)
        return true;
    }
  } else if(sf == ef && ss > es) {
    for(char c = ss - 1; c >= es + 1; c--) {
      if((*this)(std::make_pair(sf, c)) != NULL)
        return true;
    }
  }
  return false;
}

/* Checks for obstruction for Queen
 */
bool Board::obs_Q(pair<char, char> start, pair<char, char> end) const {
  if(obs_B(start, end) || obs_R(start, end))
    return true;
  return false;
}

/* Checks for obstruction for Pawn, white
 */
bool Board::obs_P(pair<char, char> start, pair<char, char> end) const {
  if(start.second == '2' && start.second + 1 != end.second) {
    pair<char, char> temp = std::make_pair(start.first, start.second + 1);
    if((*this)(temp) != NULL)
       return true;
  }
  return false;
}

/* Checks for obstruction for pawn, black
 */
bool Board::obs_p(pair<char, char> start, pair<char, char> end) const {
  if(start.second == '7' && start.second + 1 != end.second){
    pair<char, char> temp = std::make_pair(start.first, start.second - 1);
    if((*this)(temp) != NULL)
       return true;
  }
  return false;
}

/* Checks for obstruction for the mystery piece
 */
bool Board::obs_M(pair<char, char> start, pair<char, char> end) const {
  if(obs_R(start, end)) //in the case of vertical or horizontal movement 
    return true;
  if((start.first - end.first)*(start.first - end.first) == (start.second - end.second)*(start.second - end.second)){ //in the case of diagonal movement
    if(obs_B(start, end))
      return true;
  }
  return false;
}


/* Helper function for display(), sets the background color at a position on the board */
void Board::set_bg(char r, char c) const {
  if ((c - r)%2 == 0)
    Terminal::color_bg(Terminal::BLUE);
  else
    Terminal::color_bg(Terminal::RED);
}

/* Displays the board to stdout
 */
void Board::display() const {
  std::cout << std::endl;
  for(char r = '8'; r >= '1'; r--) {
    std::cout << r;
    for(char c = 'A'; c <= 'H'; c++) {
      pair<char, char> position = std::make_pair(c, r);
      if((*this)(position)) {
	if((*this)(position)->is_white())
	  Terminal:: color_fg(true, Terminal::WHITE);
	else
	  Terminal:: color_fg(false, Terminal::BLACK);
	set_bg(r, c);
	std::cout << (*this)(position)->to_ascii() << " ";
	Terminal::set_default();
      }
      else {
	Terminal:: color_fg(true, Terminal::CYAN);
	set_bg(r, c);
	std::cout << '-' << " ";
	Terminal::set_default();
      }
    }
    std::cout << std::endl;
   }
   std::cout << " A B C D E F G H" << std::endl;
}


// Do not modify
/* Defines << operator for board
 * @param os the ostream we're printing out to
 * @param board a reference to current board
 * @return the ostream for linking
 */
std::ostream& operator<<(std::ostream& os, const Board& board) {
  for(char r = '8'; r >= '1'; r--) {
    for(char c = 'A'; c <= 'H'; c++) {
      const Piece* piece = board(pair<char, char>(c, r));
      if (piece)
	os << piece->to_ascii();
      else
	os << '-';
    }
    os << std::endl;
  }
  return os;
}

