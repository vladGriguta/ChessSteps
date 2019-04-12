/*
This is a file that implements the knight piece in a chess game
*/


#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

using namespace std;

class rook : public piece{
public:
	// default constructor
	rook(bool isWhite);

	// default destructor already called when base class (piece) goes out of scope

	// here is the stage where we can fully assess whether a move is allowed
	bool isMoveAllowed(square& location);

	vector<square> possibleLocations();

	// need to define a fancy way to represent the piece
	string printPiece();
};
#endif