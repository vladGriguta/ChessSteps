#include "player.h"
#include "board.h"

// constructor
player::player(string name, bool isWhite, king* inking, vector<piece*> pieces) : _name(name),
_isWhite(isWhite), _king(inking), _remainingPieces(pieces) {}

// default destructor
player::~player(){
	_name = "";
	_isWhite = 0;
	for (vector< piece* >::iterator it = _remainingPieces.begin(); it != _remainingPieces.end(); ++it)
		delete (*it);
	_remainingPieces.clear();

	for (vector< piece* >::iterator it = _capturedPieces.begin(); it != _capturedPieces.end(); ++it)
		delete (*it);
	_capturedPieces.clear();
}

string player::getName() const{
	return _name;
}

vector<piece*> player::getRemainingPieces() const{
	return _remainingPieces;
}

// return color of player
bool player::isWhite() const{
	return _isWhite;
}

// return king
piece* player::getKing() const{
	return _king;
}

// check if player is in check
bool player::inCheck() const{
	/*
	// loop through the opponent pieces
	for (vector<piece*>::iterator it_pieces = session::other_player(this->getName())->getRemainingPieces().begin();
		it_pieces != session::other_player(this->getName())->getRemainingPieces().end(); ++it_pieces)
		if ((*it_pieces)->isMoveAllowed(*(this->getKing()->getSquare())))
			return true;
	*/
	return false;
}

bool player::tryMove(square* fromLocation, square* toLocation){
	// Plan:
	// check that the move of the piece is valid (functionality of piece isMoveAllowed)
	// Treat the special cases, including:
	// pon promotion
	// king in check
	
	bool validMove = false;
	if (!this->inCheck()){
		if (fromLocation->getOccupier()->isMoveAllowed(*toLocation)){
			validMove = true;
			// change the location of the moved piece
			fromLocation->getOccupier()->setSquare(toLocation);
			toLocation->setOccupier(fromLocation->getOccupier());
			fromLocation->setOccupier(NULL);
			// check if the piece locations on the board have changed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}
		else{
			cout << "Move is not valid due to board arrangements!...\n";
			cout << "Please try again.\n";
			validMove = false;
		}
	}
	else
		validMove = false;
	return validMove;
}

bool player::tryCapture(square* fromLocation, square* toLocation){
	// Plan:
	// check that the move of the piece is valid (functionality of piece isMoveAllowed)
	// Treat the special cases, including:
	// pon promotion
	// king in check

	bool validMove = false;

	if (!this->inCheck()){
		if (fromLocation->getOccupier()->isMoveAllowed(*toLocation)){
			validMove = true;
			// first deal with the oposite piece situated in toLocation
			toLocation->getOccupier()->setSquare(NULL);
			this->addCaptured(toLocation->getOccupier());
			// session::other_player(this)->deletePiece(toLocation->getOccupier());
			toLocation->setOccupier(NULL);
			// change the location of the moved piece
			fromLocation->getOccupier()->setSquare(toLocation);
			toLocation->setOccupier(fromLocation->getOccupier());
			fromLocation->setOccupier(NULL);
			// check if the piece locations on the board have changed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}
		else
			validMove = false;
	}
	else
		validMove = false;
	return validMove;
}


// make the move by the player
// Read the move from keyboard and call the moveToSquare() function
// xi, yi
void player::move()
{
	// read positions of piece that will be moved
	while (true){
		string moveString;
		cout << "Please enter the initial square and the final square. (e.g. c2c4):\n";
		cin >> moveString;
		cin.ignore();

		try{
			cout << "Trying to read the string " << moveString<<"\n";
			int xi = int(moveString.at(0) - 'a');
			cout << char('a' + xi) << "\n";
			int yi = int(moveString.at(1)-'0')-1;
			cout << yi+1 << "\n";
			int xf = int(moveString.at(2) - 'a');
			cout << char('a'+xf) << "\n";
			int yf = int(moveString.at(3)-'0')-1;
			cout << yf+1 << "\n";

			// if one of the inputs is not in interval (0-7) repeat
			if (xi < 0 || xi > 7 || yi < 0 || yi > 7 || xf < 0 || xf > 7 || yf < 0 || yf > 7){
				cout << "The positions read were not within the limits of the chess table\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}

			// check that the initial square contains a piece of the player making the move
			else if ((board::access_board()->getSquare(xi, yi)->getOccupier() == NULL) ||
				(board::access_board()->getSquare(xi, yi)->getOccupier()->isWhite() != this->isWhite())){
				cout << "No piece of yours was found at the initial square!\n";
				continue;
			}

			// check that the destination square does not contain a piece of the player making the move
			else if (board::access_board()->getSquare(xf, yf)->getOccupier() != NULL &&
				board::access_board()->getSquare(xf, yf)->getOccupier()->isWhite() == this->isWhite()){
				cout << "A piece of yours was found at the destination square!\n";
				continue;
			}

			// treat the case when an oposite piece is captured separately
			else if (board::access_board()->getSquare(xf, yf)->getOccupier() != NULL &&
				board::access_board()->getSquare(xf, yf)->getOccupier()->isWhite() == !this->isWhite())
			{
				if (tryCapture(board::access_board()->getSquare(xi, yi), board::access_board()->getSquare(xf, yf))){
					cout << "The Piece was successfully moved!\n";
					break;
				}
				else{
					cout << "Unsuccessful due to arrangement of the board!\n";
					continue;
				}
			}

			// try to make the move when destination square is free
			else{
				cout << "Attempting at moving the piece on the board................\n";
				if (tryMove(board::access_board()->getSquare(xi, yi), board::access_board()->getSquare(xf, yf))){
					cout << "The Piece was successfully moved!\n";
					break;
				}
				else{
					cout << "Unsuccessful due to arrangement of the board!\n";
					continue;
				}
			}
		}
		catch (...){
			//cerr << exc.what();
			cout << "The string " << moveString << " could not be used to read the initial and final squares!\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
	}
}









// add piece (in case of pon promotion)
void player::addPiece(piece* new_piece){
	_remainingPieces.push_back(new_piece);
}

// add captured piece
void player::addCaptured(piece* capturedPiece){
	capturedPiece->setSquare(NULL);
	_capturedPieces.push_back(capturedPiece);
}
