#include "king.h"

// default constructor
king::king(bool isWhite) : piece(isWhite) {}

// the check move function
bool king::isMoveAllowed(square& location){

	int translationX = abs(location.getX() - this->getSquare()->getX());
	int translationY = abs(location.getY() - this->getSquare()->getY());

	// easy cases are when the sum of absolute translations is 1 or 2
	// and there is no occupier on the location
	if (location.getOccupier() == NULL && ((translationX + translationY) > 0) &&
		(translationX < 2) && (translationY < 2))
		return true;
	// implement castle (later)
	else
		return false;
}

vector<square> king::possibleLocations(){
	vector<square> locations;
	// brute force for now
	for (int i = 0; i < 64; i++){
		square currentSquare = square(i);
		if (this->isMoveAllowed(currentSquare))
			locations.push_back(currentSquare);
	}
	return locations;
}

string king::printPiece(){
	if (this->isWhite() == true)
		return "WK";
	else
		return "BK";
}