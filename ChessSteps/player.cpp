#include<algorithm>

#include "player.h"
#include "board.h"
#include "session.h"

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
	// loop through the opponent pieces
	for (vector<piece*>::iterator it_pieces = session::other_player(this->getName())->_remainingPieces.begin();
		it_pieces != session::other_player(this->getName())->_remainingPieces.end(); ++it_pieces)
		if ((*it_pieces)->isMoveAllowed(*(this->getKing()->getSquare())))
			return true;
	return false;
}

bool player::inCheckMate(){

	if (this->inCheck())
	{
		cout << "Checking if the player is in check mate........\n";
		for (vector<piece*>::iterator it_pieces = _remainingPieces.begin(); it_pieces != _remainingPieces.end(); ++it_pieces)
		{
			// get the possible destination of each piece
			vector<square*> possibleDestinations = (*it_pieces)->possibleLocations();
			for (vector<square*>::iterator it_loc = possibleDestinations.begin(); it_loc != possibleDestinations.end(); ++it_loc){
				// check which try function is appropriate
				if ((*it_loc)->getOccupier() != NULL && (*it_loc)->getOccupier()->isWhite() == this->isWhite())
				{
					// tryCapture function
					if (tryCapture((*it_pieces)->getSquare(), (*it_loc))){
						cout << "Found that the player is not in check mate!!!\n";
						cout << "One possible move to get out of check is: ";
						cout << "from " << (*it_pieces)->getSquare()->getX() << ", " << (*it_pieces)->getSquare()->getY()
							<< "\nto " << (*it_loc)->getX() << ", " << (*it_loc)->getY() << "\n";
						return false;
					}
				}
				else{
					// tryMove function
					if (tryMove((*it_pieces)->getSquare(), (*it_loc)))
					{
						// reverse the move and return false
						// session::reverseOneMove();
						cout << "Found that the player is not in check mate!!!\n";
						cout << "One possible move to get out of check is: ";
						cout << "from " << (*it_pieces)->getSquare()->getX() << ", " << (*it_pieces)->getSquare()->getY()
							<< "\nto " << (*it_loc)->getX() << ", " << (*it_loc)->getY() << "\n";
						return false;
					}
				}
			}
		}
	}
	else{
		return false;
	}
	return true;
}

bool player::tryMove(square* fromLocation, square* toLocation){
	// Plan:
	// check that the move of the piece is valid (functionality of piece isMoveAllowed)
	// Treat the special cases, including:
	// pon promotion
	// king in check
	
	bool validMove = false;
	bool currentState = this->inCheck();
	{
		if (fromLocation->getOccupier()->isMoveAllowed(*toLocation)){
			// execute the move temporarily, then check if the new position player is in check

			validMove = true;
			// change the location of the moved piece
			fromLocation->getOccupier()->setSquare(toLocation);
			//cout << toLocation->getOccupier()->getNumberMoves() << "\n";
			toLocation->setOccupier(fromLocation->getOccupier());
			fromLocation->setOccupier(NULL);
			// increment the number of moves of the piece
			toLocation->getOccupier()->incrementMoves();
			
			// if player in check, go back and un-validate the move
			if (this->inCheck()){
				if (currentState)
					cout << "Try to get out of check!\n";
				else
					cout << "The move that you executed got you in check! Be cautious!\n";

				validMove = false;
				// change back the location of the moved piece
				fromLocation->setOccupier(toLocation->getOccupier());
				fromLocation->getOccupier()->setSquare(fromLocation);
				toLocation->setOccupier(NULL);
				// decrement the number of moves of the piece
				fromLocation->getOccupier()->decrementMoves();

			}

			// in case of pons, check if can be promoted
			if (board::access_board()->isEndRow(*toLocation)){
				toLocation->getOccupier()->promotion();
			}
		}
		else{
			cout << "Unsuccessfull! The path between the squares is not clear!!\n";
			validMove = false;
		}
	}
	return validMove;
}

bool player::tryCapture(square* fromLocation, square* toLocation){
	// Plan:
	// check that the move of the piece is valid (functionality of piece isMoveAllowed)
	// Treat the special cases, including:
	// pon promotion
	// king in check

	bool validMove = false;
	bool currentState = this->inCheck();
	{
		if (fromLocation->getOccupier()->isMoveAllowed(*toLocation)){

			validMove = true;
			// first deal with the oposite piece situated in toLocation
			toLocation->getOccupier()->setSquare(NULL);
			piece* tempCaptured = toLocation->getOccupier();
			this->addCaptured(toLocation->getOccupier());
			session::other_player(this->getName())->deletePiece(toLocation->getOccupier());

			// change the location of the moved piece
			fromLocation->getOccupier()->setSquare(toLocation);
			toLocation->setOccupier(NULL);
			toLocation->setOccupier(fromLocation->getOccupier());
			fromLocation->setOccupier(NULL);

			// increment the number of moves of the piece
			toLocation->getOccupier()->incrementMoves();

			// if player in check, go back and un-validate the move
			if (this->inCheck()){
				if (currentState)
					cout << "Try to get out of check!\n";
				else
					cout << "The move that you executed got you in check! Be cautious!\n";

				validMove = false;
				fromLocation->setOccupier(toLocation->getOccupier());
				fromLocation->getOccupier()->setSquare(fromLocation);

				toLocation->setOccupier(tempCaptured);
				tempCaptured->setSquare(toLocation);

				session::other_player(this->getName())->addPiece(tempCaptured);

				// decrement the number of moves of the piece
				fromLocation->getOccupier()->decrementMoves();

			}

			// check whether promotion is appropriate and apply it for the case of pons
			if (board::access_board()->isEndRow(*toLocation)){
				toLocation->setOccupier(toLocation->getOccupier()->promotion());
			}
		}
		else{
			cout << "Unsuccessfull! The path between the squares is not clear!!\n";
			validMove = false;
		}
	}
	return validMove;
}


// make the move by the player
// Read the move from keyboard and call the moveToSquare() function
// xi, yi
void player::move()
{
	// read positions of piece that will be moved
	while (true){
		board::access_board()->showBoard(this->isWhite());
		string moveString;
		cout << "Player " << this->getName() << " is on the move.\n";
		if (this->inCheck()){
			cout << "Bear in mind that you are in check!\n";
		}
		cout << "Please enter the initial square and the final square. (e.g. c2c4):\n";
		cin >> moveString;
		cin.ignore();

		// initialize square locations with unrealistic values
		int xi(8), yi(8), xf(8), yf(8);

		try{
			cout << "Trying to read the string " << moveString << "\n";
			xi = int(moveString.at(0) - 'a');
			//cout << char('a' + xi) << "\n";
			yi = int(moveString.at(1) - '0') - 1;
			//cout << yi + 1 << "\n";
			xf = int(moveString.at(2) - 'a');
			//cout << char('a' + xf) << "\n";
			yf = int(moveString.at(3) - '0') - 1;
			//cout << yf + 1 << "\n";
		}
		catch (...){
			//cerr << exc.what();
			cout << "The string " << moveString << " could not be used to read the initial and final squares!\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

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
			if (tryCapture(board::access_board()->getSquare(xi, yi),
				board::access_board()->getSquare(xf, yf)))
			{
				cout << "The Piece was successfully moved!\n";
				break;
			}
			else{
				cout << "Please try again!\n";
				continue;
			}
		}

		// try to make the move when destination square is free
		else{
			cout << "Attempting at moving the piece on the board................\n";
			if (tryMove(board::access_board()->getSquare(xi, yi),
				board::access_board()->getSquare(xf, yf)))
			{
				cout << "The Piece was successfully moved!\n";
				break;
			}
			else{
				cout << "Unsuccessful due to arrangement of the board!\n";
				continue;
			}
		}
	}
}



// add piece (in case of pon promotion)
void player::addPiece(piece* new_piece){
	_remainingPieces.push_back(new_piece);
}

// add captured piece
void player::addCaptured(piece* capturedPiece){
	_capturedPieces.push_back(capturedPiece);
}

void player::deletePiece(piece* ownCapturedPiece){
	// find pointer ownCapturedPiece in vector of pointers _remainingPieces
	auto positionToDelete = find(_remainingPieces.begin(), _remainingPieces.end(), ownCapturedPiece);
	_remainingPieces.erase(positionToDelete);
	// Now delete the piece from the board
	ownCapturedPiece->setSquare(NULL);
}


void player::deleteCapturedPiece(piece* oppositeCapturedPiece){
	// erase the piece from the vector of captured pieces
	auto positionToDelete = find(_capturedPieces.begin(), _capturedPieces.end(), oppositeCapturedPiece);
	_capturedPieces.erase(positionToDelete);
}