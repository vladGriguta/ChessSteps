/*
This is a file that implements the knight piece in a chess game
*/


#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

using namespace std;

class queen : public piece{
public:
	// default constructor
	queen(bool isWhite);

	virtual queen* clone() const;
	// default destructor already called when base class (piece) goes out of scope

	// here is the stage where we can fully assess whether a move is allowed
	bool isMoveAllowed(square& location);


	// need to define a fancy way to represent the piece
	string printPiece() const;
};
#endif