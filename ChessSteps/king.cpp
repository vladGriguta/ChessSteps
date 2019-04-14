#include "king.h"
#include "board.h"

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

	// implement castle
	else if ((translationX == 2 && translationY == 0) && this->getNumberMoves() == 0)
	{
		// get which rook should be checked
		int x_rook = location.getX() > this->getSquare()->getX() ? 7 : 0;
		int y_rook = this->isWhite() ? 0 : 7;

		// if the rook towards which the king moves has not moved
		if (board::access_board()->getSquare(x_rook, y_rook)->getOccupier()->getNumberMoves() == 0){
			// if the path to the rook is clear
			if (board::access_board()->isHorizontalClear(*(this->getSquare()), *(board::access_board()->getSquare(x_rook, y_rook)))){
				cout << "Castle should be executed\n";
				return true;
			}
		}
	}
	else
		return false;
}

string king::printPiece() const{
	if (this->isWhite() == true)
		return "WK";
	else
		return "BK";
}