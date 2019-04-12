/*
Write the functions defined in the piece.h header.

*/
#include "piece.h"

// default costructor
piece::piece(bool isWhite) {
	_isWhite = isWhite;
	_square = NULL;
	_hasMoved = false;
}

piece::~piece(){
	_isWhite = NULL;
	_hasMoved = NULL;
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

