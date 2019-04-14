/*
This file implements the class 'player'.
The class player is used to retain all data
related to one player in the chess game, together
with its inherited functionality.
This data is:
- color of player (boolean)
- one king, with the inherited functionality of checking whether
the player is checked after each move
- all pieces the player has left on the board (excluding king)
- all pieces that the player captured during game
*/

#ifndef PLAYER_H
#define PLAYER_H

#include<iostream>
#include<vector>

#include "king.h"

using namespace std;

class player{
private:
	string _name;
	bool _isWhite;
	vector<piece*> _remainingPieces;
	vector<piece*> _capturedPieces;
	king* _king;

public:
	// Only parametrised costructor
	player(string name, bool isWhite, king* inking, vector<piece*> pieces);

	// Copy constructor
	player(const player &pl);

	// default destructor
	~player();

	// Copy assignment operator
	player & operator=(const player &pl);
	void overwritePlayer(const player &pl);

	// get name (needed for checks in session class)
	string getName() const;

	// return the remaining pieces
	vector<piece*> getRemainingPieces() const;
	vector<piece*> getCapturedPieces() const;

	// return color of player
	bool isWhite() const;

	// get king
	king* getKing() const;

	// check if player is in check
	bool inCheck() const;

	// check if player in check mate
	bool inCheckMate();

	// try to execute one move
	bool tryMove(square* fromLocation, square* toLocation);

	// try to execute one move and capture an oposite piece
	bool tryCapture(square* fromLocation, square* toLocation);

	// make an actual move
	void move();

	// append to captured pieces
	void addCaptured(piece* capturedPiece);

	// delete own piece
	void deletePiece(piece* ownCapturedPiece);

	// delete piece from captured pieces
	void deleteCapturedPiece(piece* oppositeCapturedPiece);

	// append new piece to player (in case of promotion)
	void addPiece(piece* newPiece);
};

#endif