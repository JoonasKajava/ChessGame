#pragma once
#include "Piece.h"
#include "Station.h"

class Pawn : public Piece {
public:
	Pawn(bool isWhite) : Piece(PAWN, isWhite) {};
	void giveMovements(std::list<Move>& moves, sf::Vector2i start, Station* station);
};