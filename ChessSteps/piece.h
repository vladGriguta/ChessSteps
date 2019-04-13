/*
This file define the abstract base class piece.
'piece' will be use as an interface for all pieces defined (rook, knight, etc.)
'piece' will implement the following functionalities:
	- return color, previous positions, if_moved of piece
	- return possible moves (without considering other pieces, to avoid double )
*/



#ifndef PIECE_H
#define PIECE_H

#include<vector>
#include <istream>
#include "square.h"

class piece
{
protected:
	bool _isWhite;
	square* _square;
	int _numberMoves;

public:
	// Constructor 
	piece(bool _isWhite);
	// Default destructor (pure virtual)
	~piece();

	// Set and get location (_square) and boolean for color
	void setSquare(square* location);
	square* getSquare() const;
	bool isWhite() const;

	// Function to check whether a move is allowed (but does not move)
	// This check is done for each piece in part (rook, knight, etc..)
	virtual bool isMoveAllowed(square& location) = 0;

	int getNumberMoves() const;
	void incrementMoves();
	void decrementMoves();

	// define virtual function for pon promotion (indeed, only overriden in class pon)
	virtual piece* promotion();

	// return possible locations to move the piece
	vector<square*> possibleLocations();

	// need to define a fancy way to represent the piece
	virtual string printPiece() const = 0;
};
#endif