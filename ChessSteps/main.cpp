#include <exception>

#include "board.h"
#include "player.h"
#include "rook.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "pon.h"

int main()
{
	// First initialize the board

	////////////////// WHITE PLAYER ////////////////////////////
	square* wSquare;
	piece* wPiece;
	king* wKing;

	// Then all pieces
	vector<piece*>_whitePieces = *(new vector<piece*>);
	player* _whitePlayer;

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

	board::access_board()->showBoard(true);
	_whitePlayer->move();
	board::access_board()->showBoard(true);
	_whitePlayer->move();
	board::access_board()->showBoard(true);
	_whitePlayer->move();
	board::access_board()->showBoard(true);
	_whitePlayer->move();
	board::access_board()->showBoard(true);
	////////////////////////////////////////////////////////////////////////////
	return 0;
}