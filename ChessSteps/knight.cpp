#include "knight.h"
#include "board.h"

// default constructor
knight::knight(bool _isWhite) : piece(_isWhite) {}

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

vector<square> knight::possibleLocations(){
	vector<square> locations;
	// brute force for now
	for (int i = 0; i < 64; i++){
		square currentSquare = square(i);
		if (this->isMoveAllowed(currentSquare))
			locations.push_back(currentSquare);
	}
	return locations;
}

string knight::printPiece(){
	if (this->isWhite() == true)
		return "WN";
	else
		return "BN";
}