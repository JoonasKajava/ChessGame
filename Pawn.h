#pragma once
#include "Piece.h"
#include "Station.h"

class Pawn : public Piece {
public:
	Pawn(bool isWhite) : Piece(PAWN, isWhite) {};
	void giveMovements(std::vector<Move>& moves, sf::Vector2i start, Station* station);
	void givePromotionMovements(std::vector<Move>& moves, Move* move, Station* station);
};