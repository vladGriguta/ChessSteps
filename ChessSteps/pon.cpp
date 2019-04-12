#include "pon.h"
#include "queen.h"
#include "board.h"

// default constructor
pon::pon(bool _isWhite) : piece(_isWhite) {}

// default destructor
pon::~pon() {
	_isWhite = NULL;
	_hasMoved = NULL;
	delete _square;
}

// the check move function
bool pon::isMoveAllowed(square& location){

	bool allowed = false;
	// Treat each case in part. Start with simple move on the vertical
	int translationX = int(location.getX()) - int(this->getSquare()->getX());
	int translationY = location.getY() - this->getSquare()->getY();

	// to keep same convention for both sides, take the negative of the black y translation
	if (!this->isWhite())
		translationY = (-1) * translationY;

	// There are 4 cases that need treatment
	// valid move if moving 1 square forward to unoccupied square
	if ((location.getOccupier() == NULL) && translationY == 1 && translationX == 0){
		allowed =  true;
	}

	// second case is the oportunity to move 2 spaces the first time
	else if (!(this->_hasMoved) && translationY == 2 && translationX == 0 &&
		board::access_board()->isVerticalClear(*(this->getSquare()), location))
	{
		allowed = true;
	}

	// valid move if capturing a piece on adjacent diagonal
	else if ((location.getOccupier()->isWhite() == this->isWhite()) && translationY == 1 &&
		abs(translationX) == 1)
	{
		allowed = true;
	}

	else{
		allowed = false;
	}

	return allowed;
}

vector<square> pon::possibleLocations(){
	vector<square> locations;
	// brute force for now
	for (int i = 0; i < 64; i++){
		square currentSquare = square(i);
		if (this->isMoveAllowed(currentSquare))
			locations.push_back(currentSquare);
	}
	return locations;
}

void pon::promotion(){
	// in the special case of promotion, delete the pon and create a new piece to replace it
	// always promote to queen for now
	
	square* current_square = this->_square;
	piece* newPiece = new queen(this->isWhite());

	newPiece->setSquare(current_square);
	current_square->setOccupier(newPiece);
	// current piece goes out of scope
	this->~pon();
}

string pon::printPiece(){
	if (this->isWhite() == true)
		return "WP";
	else
		return "BP";
}
