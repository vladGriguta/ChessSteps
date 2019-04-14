/*
This is a the file that initialises and runs the game.
The class 'game' is the main interface for the chess game,
implementing all fnctionalities according to the known rules
of chess.

*/

#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include <stack>

#include "board.h"
#include "player.h"

class square;


using namespace std;

class session
{
private:
	static player* _whitePlayer;
	static vector<piece*> _whitePieces;
	static player* _blackPlayer;
	static vector<piece*> _blackPieces;

	static player* _currentPlayer;

	// elements that act as a buffer for current state of game
	static stack<player> _bufferWhitePlayer;
	static stack<player> _bufferBlackPlayer;
	static stack<board> _bufferBoard;

public:
	// initializer
	static void initialize();

	// destructor
	~session();

	static void stackCurrentState();
	static void reverseOneMove();

	// run session
	void runSession();

	// return the other player (need to check if in check)
	static player* other_player(string current_player_name);

};
#endif