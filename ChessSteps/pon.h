/*
This is a file that implements the knight piece in a chess game
*/


#ifndef PON_H
#define PON_H

#include "piece.h"

using namespace std;


class pon : public piece {
public:
	// default constructor
	pon(bool isWhite);

	// default destructor already called when base class (piece) goes out of scope
	~pon();

	// here is the stage where we can fully assess whether a move is allowed
	bool isMoveAllowed(square& location);
	//bool moveToSquare(player* byPlayer, square& location);
	vector<square> possibleLocations();

	// This class has a special functionality: Promotion
	void promotion();


	// need to define a fancy way to represent the piece
	string printPiece();
};
#endif