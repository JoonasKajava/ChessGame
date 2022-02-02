#pragma once
#include "Piece.h"
#include "Station.h"

class Rook : public Piece {
public:
	Rook(bool isWhite) : Piece(ROOK, isWhite) {};
	void giveMovements(std::list<Move>& moves, sf::Vector2i start, Station* station, bool isWhite);
};