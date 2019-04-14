/*
This file implements the class board.
The class 'board' stores all information related to each
square of the chess board game.
Because it has access to all dependencies, the class 'board'
implements the functionalities required for checking whether
a move is allowed. These functionalities are:
	- isVerticalClear(initialSquare,finalSquare);
	- isHorizontalClear(initialSquare,finalSquare);
	- isDiagonalClear(initialSquare,finalSquare);
	- isEndRow(Square)

*/

#ifndef BOARD_H
#define BOARD_H

#include<iostream>
#include<string>
#include "square.h"

class board{
private:
	
	// declare the board as a static instance of the class board that is
	// then the same for all instances
	static board* _board;

	board* _boardAsBuffer;
	// define 2D array for easy access within the class
	square* _squares[8][8];

public:

	// default constructor
	board();

	// copy assignment
	//board(const board &b);

	board* clone() const;

	// access the static member board
	static board* access_board();

	board* access_buffer();

	// overwrite the board with a previous version of it
	void overwriteBoard(board& previousBoard);

	// Default destructor
	~board();

	// access square
	square* getSquare(int x, int y);

	// move check functionalities
	bool isVerticalClear(const square& initialSquare,const square& finalSquare) const;
	bool isHorizontalClear(const square& initialSquare,const square& finalSquare) const;
	bool isDiagonalClear(const square& initialSquare,const square& finalSquare) const;
	bool isEndRow(const square& currentSquare) const;

	void showBoard(bool isWhite);
};
#endif