#pragma once
#include "Piece.h"
#include "Station.h"

class Queen : public Piece {
public:
	Queen(bool isWhite) : Piece(QUEEN, isWhite) {};
	void giveMovements(std::list<Move>& moves, sf::Vector2i start, Station* station, bool isWhite);
};