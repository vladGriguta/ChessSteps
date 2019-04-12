/*
This script defines the class square.
The class 'square' is the building block of the class board.
The members of this class are:
	- horizontal position x (a-h) and vertical position y (1-8)
	- instance of class piece or NULL
The functionalities of this class are:
	- 
*/

#ifndef SQUARE_H
#define SQUARE_H

class piece;

using namespace std;

class square{


private:
	int _x;
	int _y;
	piece* _piece;

public:
	// default constructor
	square();
	// parametrised constructor using 2D map
	square(int x, int y);
	// parametrised constructor using 1D vector
	square(int pos);
	// default destructor
	~square();

	// get positions
	int getX() const;
	int getY() const;

	// set piece
	void setOccupier(piece* _piece);

	// return piece (or NULL if none)
	piece* getOccupier() const;
};


#endif