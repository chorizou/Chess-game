CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0

CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

#Target to create chess executable
chess: main.o Chess.o Board.o CreatePiece.o King.o Queen.o Rook.o Knight.o Bishop.o Pawn.o
	$(CC) main.o Chess.o Board.o CreatePiece.o King.o Queen.o Rook.o Knight.o Bishop.o Pawn.o -o chess

# Compiles main.cpp into an object file
main.o: main.cpp Chess.h Board.h CreatePiece.h King.h Queen.h Rook.h Knight.h Bishop.h Pawn.h Mystery.h 
	$(CC) $(CFLAGS) -c main.cpp

# compiles Chess.cpp into an object file
Chess.o: Chess.cpp Chess.h Piece.h Board.h
	$(CC) $(CFLAGS) -c Chess.cpp

# compiles Board.cpp into an object file
Board.o: Board.cpp Board.h Piece.h CreatePiece.h
	$(CC) $(CFLAGS) -c Board.cpp

# Compiles CreatePiece.cpp into an object file
CreatePiece.o: CreatePiece.cpp CreatePiece.h
	$(CC) $(CFLAGS) -c CreatePiece.cpp

# Compiles King.cpp into an object file
King.o: King.cpp King.h Piece.h
	$(CC) $(CFLAGS) -c King.cpp

# Compiles Queen.cpp into an object file
Queen.o: Queen.cpp Queen.h Piece.h
	$(CC) $(CFLAGS) -c Queen.cpp

# Compiles Rook.cpp into an object file
Rook.o: Rook.cpp Rook.h Piece.h
	$(CC) $(CFLAGS) -c Rook.cpp

# Compiles Knight.cpp into an object file
Knight.o: Knight.cpp Knight.h Piece.h 
	$(CC) $(CFLAGS) -c Knight.cpp

# Compiles Bishop.cpp into an object file
Bishop.o: Bishop.cpp Bishop.h Piece.h
	$(CC) $(CFLAGS) -c Bishop.cpp

# Compiles Pawn.cpp into an object file
Pawn.o: Pawn.cpp Pawn.h Piece.h
	$(CC) $(CFLAGS) -c Pawn.cpp

# Will remove intermediate & executable file
clean:
	rm -f *.o finalproject
