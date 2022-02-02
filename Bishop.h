#pragma once
#include "Piece.h"
#include "Station.h"

class Bishop : public Piece {
public:
	Bishop(bool isWhite) : Piece(BISHOP, isWhite) {};
	void giveMovements(std::list<Move>& moves, sf::Vector2i start, Station* station, bool isWhite);
};