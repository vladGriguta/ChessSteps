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

// copy constructor
piece::piece(piece &p){
	_isWhite = p.isWhite();
	_numberMoves = p.getNumberMoves();
	_square = p.getSquare();
}

// Coppy assignment operator
piece & piece ::operator=(piece &p){
	cout << "Copy assignment!" << endl;
	if (&p == this)
		return *this;
	// Start by deleting what the left object holds
	_numberMoves = 0;
	_isWhite = 0;
	_square = NULL;
	if (p.getSquare() != NULL){
		_square = new square(p.getSquare()->getX(), p.getSquare()->getY());
	}
	// Coppy the variables
	_numberMoves = p.getNumberMoves(); _isWhite = p.isWhite();
	return *this;
}

void piece::overwritePiece(piece &p){
	_numberMoves = 0;
	_isWhite = 0;
	_square = NULL;
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
		{
			// check that the destination square does not contain a piece of the player making the move
			if (board::access_board()->getSquare(x, y)->getOccupier() != NULL &&
				board::access_board()->getSquare(x, y)->getOccupier()->isWhite() == this->isWhite())
			{
				continue;
			}
			// finaly check if move is allowed
			else if (this->isMoveAllowed(*(board::access_board()->getSquare(x, y))))
			{
				locations.push_back(board::access_board()->getSquare(x, y));
			}
		}
	return locations;
}