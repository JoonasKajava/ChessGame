#pragma once
#include "Piece.h"

enum direction {Left, Right};

class King : public Piece {
public:
	King(bool isWhite);
	bool canCastle(direction direction, Station* station);
	void giveMovements(std::list<Move>& moves, sf::Vector2i start, Station* station, bool isWhite);
};