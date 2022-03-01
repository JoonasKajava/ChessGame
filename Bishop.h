#pragma once
#include "Piece.h"
#include "Station.h"

class Bishop : public Piece {
public:
	Bishop(bool isWhite) : Piece(BISHOP, isWhite) {};
	void giveMovements(std::vector<Move>& moves, sf::Vector2i start, Station* station);
};