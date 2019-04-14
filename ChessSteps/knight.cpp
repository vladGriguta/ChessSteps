#include "knight.h"
#include "board.h"

// default constructor
knight::knight(bool _isWhite) : piece(_isWhite) {}

knight* knight::clone() const {
	return new knight(this);
}

// the check move function
bool knight::isMoveAllowed(square& location){
	int translationX = abs(location.getX() - this->getSquare()->getX());
	int translationY = abs(location.getY() - this->getSquare()->getY());

	// the knight i the only chess piece that can jump over other pieces
	// therefore, only check if one translation is 1 and the other is 2
	if ((translationX + translationY) == 3 && (translationX * translationY) == 2)
		return true;
	else
		return false;
}

string knight::printPiece() const{
	if (this->isWhite() == true)
		return "WN";
	else
		return "BN";
}