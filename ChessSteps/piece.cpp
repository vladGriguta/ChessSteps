/*
Write the functions defined in the piece.h header.

*/
#include "piece.h"
#include "board.h"

// default costructor
piece::piece(bool isWhite) {
	_isWhite = isWhite;
	_square = NULL;
	_numberMoves = 0;
}

piece::~piece(){
	_isWhite = NULL;
	_numberMoves = 0;
	delete _square;
}

void piece::setSquare(square* location){
	_square = location;
}

square* piece::getSquare() const{
	return _square;
}

bool piece::isWhite() const{
	return _isWhite;
}


int piece::getNumberMoves() const{
	return _numberMoves;
}

void piece::incrementMoves(){
	_numberMoves = _numberMoves + 1;
}

void piece::decrementMoves(){
	_numberMoves = _numberMoves - 1;
}

piece* piece::promotion(){
	// return the same piece for all cases except when dealing with a pon
	return this;
}

vector<square*> piece::possibleLocations()
{
	vector<square*> locations;
	// brute force for now
	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++)
			if (this->isMoveAllowed(*(board::access_board()->getSquare(x, y)))){
				locations.push_back(board::access_board()->getSquare(x, y));
			}
	return locations;
}