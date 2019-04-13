#include "rook.h"
#include "board.h"

// default constructor
rook::rook(bool _isWhite) : piece(_isWhite) {}

// the check move function
bool rook::isMoveAllowed(square& location){
	// check if moving along a clear vertical
	if (board::access_board()->isVerticalClear(*(this->getSquare()), location))
		return true;
	// valid move if moving on a clear horizontal
	else if (board::access_board()->isHorizontalClear(*(this->getSquare()), location))
		return true;
	else
		return false;
}

string rook::printPiece() const{
	if (this->isWhite() == true)
		return "WR";
	else
		return "BR";
}