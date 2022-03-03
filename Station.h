#pragma once

#include "Piece.h"
#include "Jail.h"
#include "Move.h"
#include "MinMaxReturn.h"

class Pawn;

class Station {
	bool _isKingInDanger = false;

public:
	bool _isMainStation = false;
	Station(bool createPieces = false);
	Piece *board[8][8];
	bool _isWhiteTurn = true;
	bool gameOver = false;


	Jail _whiteJail = Jail(sf::Vector2f(910, 510), sf::Vector2f(300, 300));
	Jail _blackJail = Jail(sf::Vector2f(910, 10), sf::Vector2f(300, 300));

	void giveAllLegalMoves(std::vector<Move>& list);

	Pawn *enPassantBuffer = 0;

	std::vector<Piece*> movedPieces;

	void movePiece(Move move, bool shouldEndTurn = true);

	double evaluate();

	MinMaxReturn miniMax(MinMaxReturn alpha, MinMaxReturn beta, int depth, Station* station);

	bool setIsKingInDanger();
	bool getIsKingInDanger();
};