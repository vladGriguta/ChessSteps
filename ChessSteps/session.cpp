#include "session.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "pon.h"
#include "square.h"


player* session::_whitePlayer = NULL;
player* session::_blackPlayer = NULL;
player* session::_currentPlayer = NULL;
vector<piece*> session::_whitePieces;
vector<piece*> session::_blackPieces;


// initialize the buffer static objects as well
stack<player> session::_bufferWhitePlayer;
stack<player> session::_bufferBlackPlayer;
stack<board> session::_bufferBoard;


void session::initialize(){
	// this function aims at initializing the board with all pieces and the
	// two players


	////////////////// WHITE PLAYER ////////////////////////////
	square* wSquare;
	piece* wPiece;
	king* wKing;

	// Then all pieces
	vector<piece*>_whitePieces = *(new vector<piece*>);

	// WHITE ROOK
	wPiece = new rook(true);
	wSquare = board::access_board()->getSquare(0, 0);
	wSquare->setOccupier(wPiece);
	wPiece->setSquare(wSquare);
	_whitePieces.push_back(wPiece);
	wPiece = new rook(true);
	wSquare = board::access_board()->getSquare(7, 0);
	wSquare->setOccupier(wPiece);
	wPiece->setSquare(wSquare);
	_whitePieces.push_back(wPiece);

	// WHITE KNIGHT
	wPiece = new knight(true);
	wSquare = board::access_board()->getSquare(1, 0);
	wSquare->setOccupier(wPiece);
	wPiece->setSquare(wSquare);
	_whitePieces.push_back(wPiece);
	wPiece = new knight(true);
	wSquare = board::access_board()->getSquare(6, 0);
	wSquare->setOccupier(wPiece);
	wPiece->setSquare(wSquare);
	_whitePieces.push_back(wPiece);

	// WHITE BISHOP
	wPiece = new bishop(true);
	wSquare = board::access_board()->getSquare(2, 0);
	wSquare->setOccupier(wPiece);
	wPiece->setSquare(wSquare);
	_whitePieces.push_back(wPiece);
	wPiece = new bishop(true);
	wSquare = board::access_board()->getSquare(5, 0);
	wSquare->setOccupier(wPiece);
	wPiece->setSquare(wSquare);
	_whitePieces.push_back(wPiece);

	// WHITE QUEEN
	wPiece = new queen(true);
	wSquare = board::access_board()->getSquare(3, 0);
	wSquare->setOccupier(wPiece);
	wPiece->setSquare(wSquare);
	_whitePieces.push_back(wPiece);

	// WHITE KING
	wKing = new king(true);
	wSquare = board::access_board()->getSquare(4, 0);
	wSquare->setOccupier(wKing);
	wKing->setSquare(wSquare);

	// WHITE PONS
	for (int i = 0; i < 8; i++){
		wPiece = new pon(true);
		wSquare = board::access_board()->getSquare(i, 1);
		wSquare->setOccupier(wPiece);
		wPiece->setSquare(wSquare);
		_whitePieces.push_back(wPiece);
	}
	_whitePlayer = new player("White Player", true, wKing, _whitePieces);


	////////////////// BLACK PLAYER ////////////////////////////
	square* bSquare;
	piece* bPiece;
	king* bKing;

	// Then all pieces
	vector<piece*>_blackPieces = *(new vector<piece*>);

	// BLACK ROOK
	bPiece = new rook(false);
	bSquare = board::access_board()->getSquare(0, 7);
	bSquare->setOccupier(bPiece);
	bPiece->setSquare(bSquare);
	_blackPieces.push_back(bPiece);
	bPiece = new rook(false);
	bSquare = board::access_board()->getSquare(7, 7);
	bSquare->setOccupier(bPiece);
	bPiece->setSquare(bSquare);
	_blackPieces.push_back(bPiece);

	// BLACK KNIGHT
	bPiece = new knight(false);
	bSquare = board::access_board()->getSquare(1, 7);
	bSquare->setOccupier(bPiece);
	bPiece->setSquare(bSquare);
	_blackPieces.push_back(bPiece);
	bPiece = new knight(false);
	bSquare = board::access_board()->getSquare(6, 7);
	bSquare->setOccupier(bPiece);
	bPiece->setSquare(bSquare);
	_blackPieces.push_back(bPiece);

	// BLACK BISHOP
	bPiece = new bishop(false);
	bSquare = board::access_board()->getSquare(2, 7);
	bSquare->setOccupier(bPiece);
	bPiece->setSquare(bSquare);
	_blackPieces.push_back(bPiece);
	bPiece = new bishop(false);
	bSquare = board::access_board()->getSquare(5, 7);
	bSquare->setOccupier(bPiece);
	bPiece->setSquare(bSquare);
	_blackPieces.push_back(bPiece);

	// BLACK QUEEN
	bPiece = new queen(false);
	bSquare = board::access_board()->getSquare(3, 7);
	bSquare->setOccupier(bPiece);
	bPiece->setSquare(bSquare);
	_blackPieces.push_back(bPiece);

	// BLACK KING
	bKing = new king(false);
	bSquare = board::access_board()->getSquare(4, 7);
	bSquare->setOccupier(bKing);
	bKing->setSquare(bSquare);

	// BLACK PONS
	for (int i = 0; i < 8; i++){
		bPiece = new pon(false);
		bSquare = board::access_board()->getSquare(i, 6);
		bSquare->setOccupier(bPiece);
		bPiece->setSquare(bSquare);
		_blackPieces.push_back(bPiece);
	}
	_blackPlayer = new player("Black Player", false, bKing, _blackPieces);


	// First player to move is white
	_currentPlayer = _whitePlayer;
}

void session::stackCurrentState(){
	player tempWhitePlayer(*_whitePlayer);
	_bufferWhitePlayer.push(tempWhitePlayer);
	cout << "Name of player copy " << tempWhitePlayer.getName() << "\n";
	cout << "Name of player player " << _whitePlayer->getName() << "\n";
	cout << "Address of copy: " << &tempWhitePlayer << "\n";
	cout << "Address of player: " << _whitePlayer << "\n";
	player tempBlackPlayer(*_blackPlayer);
	_bufferBlackPlayer.push(tempBlackPlayer);
	cout << "Got here in stack!!\n";
	//board tempBoard(*(board::access_board()));
	cout << "Got to the end of board copy constructor!\n";
	//_bufferBoard.push(tempBoard);
	_bufferBoard.push(*board::access_board()->clone());
	cout << "pushed constructor to buffer!\n";
	//cout << "Address of copy: " << tempBoard.access_buffer()->getSquare(0,0) << "\n";
	cout << "Address of board: " << board::access_board()->getSquare(0,0) << "\n";
	cout << "Current state stacked!\n";
	cout << "Number of board instances saved: " << _bufferBoard.size() << "\n";
}

void session::reverseOneMove(){
	if (_bufferBoard.size() > 1){
		//cout << "Inside the reverse function...\n";
		//cout << "Name of player player " << _whitePlayer->getName() << "\n";
		//cout << "Stored piece " << _bufferWhitePlayer.top().getName() << "  " << _bufferWhitePlayer.top().isWhite() << "\n";
		_bufferWhitePlayer.pop();
		_whitePlayer->overwritePlayer((_bufferWhitePlayer.top()));
		//cout << "Name of player player " << _whitePlayer->getName() << "\n";
		//cout << "Name of player player " << _whitePlayer->getName() << "\n";
		_bufferBlackPlayer.pop();
		_blackPlayer->overwritePlayer((_bufferBlackPlayer.top()));

		_bufferBoard.pop();
		cout << "buffer has " << _bufferBoard.size() << "\n";
		board::access_board()->overwriteBoard(*(_bufferBoard.top().access_buffer()));
		//board::access_board()->showBoard(true);
		_bufferBoard.top().access_buffer()->showBoard(true);
		cout << "Inside the reverse function...\n";
	}
	else{
		cout << "You are already at the beggining of the game!!!!\n";
	}

}

void session::runSession(){
	session::initialize();
	session::stackCurrentState();
	cout << "Got here!!";
	while (true) {
		// always stack current state of the dependencies (players, board)
		if (!_currentPlayer->inCheckMate()){
			cout << "Got here!!";
			_currentPlayer->move();
			cout << "Got here!!\n";
			_currentPlayer = other_player(_currentPlayer->getName()); // works for when reverse move is called as well
		}
		else{
			cout << "The game is OVER. The winner is " << other_player(_currentPlayer->getName())->getName() << "\n\n\n";
			cout << "=================================CONGRATULATIONS=================================!\n";
			cout << "==================================" << other_player(_currentPlayer->getName())->getName()
				<< "==================================!\n\n\n";
			break;
		}
	}

}


session::~session(){
	// Delete pieces

	for (auto itr = _whitePieces.begin(); itr != _whitePieces.end(); ++itr)
		delete *itr;
	_whitePieces.clear();

	for (auto itr = _blackPieces.begin(); itr != _blackPieces.end(); ++itr)
		delete *itr;
	_blackPieces.clear();

	_whitePlayer = NULL;
	_blackPlayer = NULL;


	// Empty buffers as well
	while (!_bufferBoard.empty()){
		_bufferWhitePlayer.pop();
		_bufferBlackPlayer.pop();
		_bufferBoard.pop();
	}

}


player* session::other_player(string current_player_name){
	if (current_player_name == _whitePlayer->getName())
		return _blackPlayer;
	else if (current_player_name == _blackPlayer->getName())
		return _whitePlayer;
	else{
		cout << "Oponent of " << current_player_name << " was not identified\n";
		cout << "Black player name " << _blackPlayer->getName() << "\n";
		cout << "White player name " << _whitePlayer->getName() << "\n";
		//throw string("Error!! The name of the player could not be identified!\n");
	}
}

