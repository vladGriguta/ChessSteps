#include <iostream>
#include <string>
#include "square.h"
#include "piece.h"

// parametrised constructor using 2D map
square::square(int x, int y){
	_x = x;
	_y = y;
	_piece = NULL;
}

// copy constructor
square::square(square &sq){
	_x = sq.getX();
	_y = sq.getY();
	_piece = sq.getOccupier();
}

// Coppy assignment operator
square & square ::operator=(square &p){
	if (&p == this)
		return *this;
	// Start by deleting what the left object holds
	_x = 0;
	_y = 0;
	_piece = NULL;
	std::cout << "square assignment\n";
	if (p.getOccupier() != NULL){
		_piece = p.getOccupier()->clone();
	}
	// Coppy the variables
	_x = p.getX(); _y = p.getY();
	return *this;
}

void square::overwriteSquare(square& s){
	// std::cout << s.getOccupier()->printPiece() << "\t" << this->getOccupier()->printPiece() << "\n";
	// Start by deleting what the left object holds
	_x = 0;
	_y = 0;
	_piece = NULL;
	if (s.getOccupier() != NULL){
		_piece = s.getOccupier()->clone();
		if (s.getOccupier() == _piece)
			cout << "EVERYTHING IS WRONG!!!\n";
	}
	// Coppy the variables
	_x = s.getX(); _y = s.getY();


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
