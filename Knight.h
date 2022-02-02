#pragma once
#include "Piece.h"
#include "Station.h"

class Knight : public Piece {
public:
	Knight(bool isWhite) : Piece(KNIGHT, isWhite) {};
	void giveMovements(std::list<Move>& moves, sf::Vector2i start, Station* station, bool isWhite);
};