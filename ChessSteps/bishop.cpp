#include "bishop.h"
#include "board.h"

// default constructor
bishop::bishop(bool _isWhite) : piece(_isWhite) {}

// the check move function
bool bishop::isMoveAllowed(square& location){
	// valid move if moving on a clear diagonal
	if (board::access_board()->isDiagonalClear(*(this->getSquare()), location))
		return true;
	else
		return false;
}

vector<square> bishop::possibleLocations(){
	vector<square> locations;
	// brute force for now
	for (int i = 0; i < 64; i++){
		square currentSquare = square(i);
		if (this->isMoveAllowed(currentSquare))
			locations.push_back(currentSquare);
	}
	return locations;
}


// need to define a fancy way to represent the piece
string bishop::printPiece(){
	if (this->isWhite() == true)
		return "WB";
	else
		return "BB";
}