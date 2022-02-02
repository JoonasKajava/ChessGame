#pragma once
#include "Piece.h"
#include "Rook.h"
#include "Bishop.h"
#include "King.h"
#include "Station.h"

class Queen : public Rook, public Bishop, public King, public Piece {
public:
	Queen(bool isWhite) : Rook(isWhite), Bishop(isWhite), King(isWhite), Piece(QUEEN, isWhite) {};
	void giveMovements(std::list<Move>& moves, sf::Vector2i start, Station* station);
};