#include "board.h"
#include "piece.h"

// initialize the board at first run
board* board::_board = NULL;

// access the static member board
board* board::access_board()
{
	if (_board == NULL)
		_board = new board();
	return _board;
}


// default destructor
board::~board(){
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++)
			delete _squares[i][j];
		delete _squares[i];
		}
	delete _squares;
}

// check vertical
bool board::isVerticalClear(const square& initialSquare,const square& finalSquare) const{
	// check for horizontal move and return error if true
	if (initialSquare.getX() - finalSquare.getX() != 0)
		throw string("ERROR!! Inputs of function must be on the same horizontal.\n");
	else{
		bool sign = initialSquare.getY() < finalSquare.getY();
		int x_static = initialSquare.getX();
		// run through the squares in between and return false if any occupier is detected
		for (int y = initialSquare.getY(); y != finalSquare.getY(); y += sign)
			if (_squares[x_static][y]->getOccupier() != NULL)
				// if occupier spotted at any stage return negative
				return false;
		// if no occupier spotted return positive
		return true;
	}
}

// check vertical
bool board::isHorizontalClear(const square& initialSquare,const square& finalSquare) const{
	// check for horizontal move and return error if true
	if (initialSquare.getY() - finalSquare.getY() != 0)
		throw string("ERROR!! Inputs of function must be on the same vertical.\n");
	else{
		bool sign = initialSquare.getX() < finalSquare.getX();
		int y_static = initialSquare.getY();
		// run through the squares in between and return false if any occupier is detected
		for (int x = initialSquare.getX(); x != finalSquare.getX(); x += sign)
			if (_squares[x][y_static]->getOccupier() != NULL)
				// if occupier spotted at any stage return negative
				return false;
		// if no occupier spotted return positive
		return true;
	}
}

// check vertical
bool board::isDiagonalClear(const square& initialSquare,const square& finalSquare) const{
	// check for horizontal move and return error if true
	if ((initialSquare.getX() - finalSquare.getX()) != (initialSquare.getY() - finalSquare.getY()))
		throw string("ERROR!! Inputs of function must be on the same diagonal.\n");
	else{
		bool sign_x = initialSquare.getX() < finalSquare.getX();
		bool sign_y = initialSquare.getY() < finalSquare.getY();

		// run through the squares in between and return false if any occupier is detected
		for (int counter = 0; counter < abs(initialSquare.getX() - finalSquare.getX()); ++counter){
			int x_current = initialSquare.getX() + int(counter*sign_x);
			int y_current = initialSquare.getY() + int(counter*sign_y);
			if (_squares[x_current][y_current]->getOccupier() != NULL)
				// if occupier spotted at any stage return negative
				return false;
		}
		// if no occupier spotted return positive
		return true;
	}
}

bool board::isEndRow(const square& currentSquare) const{
	if (currentSquare.getY() == 0 || currentSquare.getY() == 7)
		return 0;
}

square* board::getSquare(int x, int y){
	return _squares[x][y];
}


void board::showBoard(bool isWhite){
	if (isWhite == true){
		for (int y = 7; y >= 0; y--){
			cout << "\t" << y + 1;
			for (int x = 0; x < 8; x++){
				if (_squares[x][y]->getOccupier() != NULL)
					cout << "\t" << _squares[x][y]->getOccupier()->printPiece();
				else
					cout << "\t" << "  ";
			}
			cout << endl;
		}
		for (char x = 'a'; x <= 'h'; x++)
			cout << "\t" << x;
		cout << endl;
		cout << "========================BOARD================================";
	}
	else{
		for (int y = 0; y < 8; y++){
			cout << "\t" << y + 1;
			for (int x = 7; x >= 0; x--){
				if (_squares[x][y]->getOccupier() == NULL)
					cout << "\t" << _squares[x][y]->getOccupier()->printPiece();
				else
					cout << "\t" << "  ";
			}
			cout << endl;
		}
		for (char x = 'h'; x >= 'a'; x--)
			cout << "\t" << x;
		cout << endl;
		cout << "========================BOARD================================";
	}
}



