#include "bishop.h"
#include "board.h"

// default constructor
bishop::bishop(bool _isWhite) : piece(_isWhite) {}

bishop* bishop::clone() const {
	return new bishop(this);
}

// the check move function
bool bishop::isMoveAllowed(square& location){
	// valid move if moving on a clear diagonal
	if (board::access_board()->isDiagonalClear(*(this->getSquare()), location))
		return true;
	else
		return false;
}


// need to define a fancy way to represent the piece
string bishop::printPiece() const{
	if (this->isWhite() == true)
		return "WB";
	else
		return "BB";
}