#pragma once

#include "Piece.h"
#include "Jail.h"
#include "Move.h"

class Pawn;

class Station {
public:
	Station();
	Piece *board[8][8];
	bool _isWhiteTurn = true;

	Jail _whiteJail = Jail(sf::Vector2f(910, 510), sf::Vector2f(300, 300));
	Jail _blackJail = Jail(sf::Vector2f(910, 10), sf::Vector2f(300, 300));

	void giveAllLegalMoves(std::list<Move>& list);

	Pawn *enPassantBuffer = 0;

	std::list<Piece*> movedPieces;

	void movePiece(Move move, bool shouldEndTurn = true);

	double evaluate();
};