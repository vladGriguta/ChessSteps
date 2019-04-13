#include "square.h"

// parametrised constructor using 2D map
square::square(int x, int y){
	_x = x;
	_y = y;
}

// parametrised constructor using 1D vector
square::square(int pos){
	_y = int(pos / 8);
	_x = int(pos % 8);
}
// default destructor
square::~square(){
	_x = 0;
	_y = 0;
	delete _piece;
}

// get positions
int square::getX() const{
	return _x;
}
int square::getY() const{
	return _y;
}

// set piece
void square::setOccupier(piece* piece){
	_piece = piece;
}

// return piece (or NULL if none)
piece* square::getOccupier(){
	return _piece;
}
