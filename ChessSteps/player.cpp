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
	/*
	for (vector< piece* >::iterator it = _remainingPieces.begin(); it != _remainingPieces.end(); ++it)
		delete (*it);
	_remainingPieces.clear();

	for (vector< piece* >::iterator it = _capturedPieces.begin(); it != _capturedPieces.end(); ++it)
		delete (*it);
	_capturedPieces.clear();
	*/
}

string player::getName() const{
	return _name;
}

vector<piece*> player::getRemainingPieces() const{
	return _remainingPieces;
}

vector<piece*> player::getCapturedPieces() const{
	return _capturedPieces;
}

// return color of player
bool player::isWhite() const{
	return _isWhite;
}

// return king
king* player::getKing() const{
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

		// temporarily disable cout
		cout.setstate(std::ios_base::failbit);

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
		cout.clear();
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
			
			// if castle happens need to move the rook as well
			if (toLocation->getOccupier()->printPiece().at(1) == 'K' && abs(toLocation->getX() - fromLocation->getX()) == 2){
				// obtain the coordinates of the rook with which to castle
				int x_rook = toLocation->getX() > fromLocation->getX() ? 7 : 0;
				int y_rook = this->isWhite() ? 0 : 7;

				// compute the new coordinates of the rook
				int x_new_rook = (x_rook==0) ? fromLocation->getX() - 1 : fromLocation->getX() + 1;
				int y_new_rook = y_rook;
				// move the rook (3 step process)
				board::access_board()->getSquare(x_rook, y_rook)->getOccupier()->
					setSquare(board::access_board()->getSquare(x_new_rook, y_new_rook));
				board::access_board()->getSquare(x_new_rook, y_new_rook)->
					setOccupier(board::access_board()->getSquare(x_rook, y_rook)->getOccupier());
				board::access_board()->getSquare(x_rook, y_rook)->setOccupier(NULL);
				// increment the number of moves of the rook
				board::access_board()->getSquare(x_new_rook, y_new_rook)->getOccupier()->incrementMoves();
			}

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
		cout << "(To return to the previous state of the board press 'r')\n";
		cin >> moveString;
		cin.ignore();

		// if ordinary move (moveString = 4 characters)
		if (moveString.length() == 4){
			// initialize square locations with unrealistic values
			int xi(8), yi(8), xf(8), yf(8);
			try{
				//cout << "Trying to read the string " << moveString << "\n";
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
					session::stackCurrentState();
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
					session::stackCurrentState();
					break;
				}
				else{
					cout << "Unsuccessful due to arrangement of the board!\n";
					continue;
				}
			}
		}
		else if(moveString.length() == 1) {
			// may request to return to previous state
			if (moveString.at(0) == 'r'){
				session::reverseOneMove();
				break;
			}
			else{
				cout << "Input " << moveString << " was not recognized.\n";
				continue;
			}
		}
		else if (moveString.length() == 2){
			// may request to see the possible moves of the piece
			// initialize square locations with unrealistic values
			int xi(8), yi(8);
			try{
				xi = int(moveString.at(0) - 'a');
				yi = int(moveString.at(1) - '0') - 1;
			}
			catch (...){
				cout << "The string " << moveString << " could not be used to read the initial square!\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			// if one of the inputs is not in interval (0-7) repeat
			if (xi < 0 || xi > 7 || yi < 0 || yi > 7){
				cout << "The positions read were not within the limits of the chess table\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			else if ((board::access_board()->getSquare(xi, yi)->getOccupier() == NULL) ||
				(board::access_board()->getSquare(xi, yi)->getOccupier()->isWhite() != this->isWhite())){
				cout << "No piece of yours was found at the initial square!\n";
				continue;
			}
			else{
				vector<square*> potentialMoves= board::access_board()->getSquare(xi, yi)->getOccupier()->possibleLocations();
				// do smth with these
				break;
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

void player::overwritePlayer(const player &pl){
	if (&pl != this){
		// Start by deleting what the left object holds
		_name = "";
		_isWhite = 0;
		_king = NULL;
		// Coppy the variables
		_name = pl.getName(); _isWhite = pl.isWhite();

		if (!_remainingPieces.empty()){
			cout << _remainingPieces.size() << endl;
			for (vector< piece* >::iterator it = _remainingPieces.begin(); it != _remainingPieces.end(); ++it){
				cout << (*it)->printPiece() << "\n";
				(*it) = NULL;
			}
			_remainingPieces.clear();
		}
		if (!_capturedPieces.empty()){
			for (vector< piece* >::iterator it = _capturedPieces.begin(); it != _capturedPieces.end(); ++it){
				(*it) = NULL;

			}
			_capturedPieces.clear();
		}
		// Coppy whole data in new vectors
		// copy values to new matrix
		vector<piece*> newRemainingPieces(pl.getRemainingPieces());
		for (vector< piece* >::iterator it = newRemainingPieces.begin(); it != newRemainingPieces.end(); ++it){
			_remainingPieces.push_back(*it);
		}
		vector<piece*> newCapturedPieces(pl.getCapturedPieces());
		for (vector< piece* >::iterator it = newCapturedPieces.begin(); it != newCapturedPieces.end(); ++it)
			_capturedPieces.push_back(*it);
	}
}

// Coppy assignment operator
player & player ::operator=(const player &pl) {
	cout << "Copy assignment!!!!!!!!!!!" << endl;
	/*
	if (&pl == this)
		return *this;
	// Start by deleting what the left object holds
	_name = "";
	_isWhite = 0;
	delete _king;
	// Coppy the variables
	_name = pl.getName(); _isWhite = pl.isWhite();
	
	cout << "Will probably stop here!!!!!!!!!";

	if (!_remainingPieces.empty()){
		cout << "Just before for loop!" << endl;
		cout << _remainingPieces.size() << endl;
		for (vector< piece* >::iterator it = _remainingPieces.begin(); it != _remainingPieces.end(); ++it){
			cout << (*it)->printPiece() << "\n";
			delete (*it);
			cout <<"Got here!\n";
		}
		cout << "Copy assignment!" << endl;
		//_remainingPieces.clear();
	}
	if (!_capturedPieces.empty()){
		cout << "Copy assignment!" << endl;
		for (vector< piece* >::iterator it = _capturedPieces.begin(); it != _capturedPieces.end(); ++it)
			delete (*it);
		cout << "Copy assignment!" << endl;
		//_capturedPieces.clear();
	}
	// Coppy whole data in new vectors
	// copy values to new matrix
	for (vector< piece* >::iterator it = pl.getRemainingPieces().begin(); it != pl.getRemainingPieces().end(); ++it)
		_remainingPieces.push_back(*it);
	for (vector< piece* >::iterator it = pl.getCapturedPieces().begin(); it != pl.getCapturedPieces().end(); ++it)
		_capturedPieces.push_back(*it);
	*/
	return *this;
}



// Copy constructor
player::player(const player & pl) : _remainingPieces(*(&pl.getRemainingPieces())), _capturedPieces(*(&pl.getCapturedPieces())), 
_name(*(&pl.getName())), _isWhite(pl.isWhite()), _king(&(*pl.getKing()))
{
	cout << "Copy constructor called!" << endl;

	/*
	// Coppy the variables
	_name = pl.getName(); _isWhite = pl.isWhite();
	_king = pl.getKing();
	// Coppy whole data in new vectors
	cout << "Gets here\n";
	*/
	/*
	_remainingPieces = vector<piece*>(pl.getRemainingPieces().size());
	for (int i = 0; i < pl.getRemainingPieces().size();i++){
		_remainingPieces[i] = pl.getRemainingPieces()[i];
	}
	
	cout << "Gets here\n";
	for (vector< piece* >::iterator it = pl.getCapturedPieces().begin(); it != pl.getCapturedPieces().end(); ++it)
		_capturedPieces.push_back(*it);
	*/
}