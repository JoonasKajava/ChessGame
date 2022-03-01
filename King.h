#pragma once
#include "Piece.h"
#include "Station.h"

enum direction {Left, Right};

class King : public Piece {
public:
	King(bool isWhite) : Piece(KING, isWhite) {};
	bool canCastle(direction direction, Station* station);
	void giveMovements(std::vector<Move>& moves, sf::Vector2i start, Station* station);
};