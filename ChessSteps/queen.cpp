#include "queen.h"
#include "board.h"

// default constructor
queen::queen(bool _isWhite) : piece(_isWhite) {}

// the check move function
bool queen::isMoveAllowed(square& location){
	// check if moving along a clear vertical
	if (board::access_board()->isVerticalClear(*(this->getSquare()), location))
		return true;
	// valid move if moving on a clear horizontal
	else if (board::access_board()->isHorizontalClear(*(this->getSquare()), location))
		return true;
	// valid move if moving on a clear diagonal
	else if (board::access_board()->isDiagonalClear(*(this->getSquare()), location))
		return true;
	else{
		return false;
	}
}

string queen::printPiece() const{
	if (this->isWhite() == true)
		return "WQ";
	else
		return "BQ";
}
