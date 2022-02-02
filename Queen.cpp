#pragma once
#include "Queen.h"

void Queen::giveMovements(std::list<Move>& moves, sf::Vector2i start, Station* station)
{
	Bishop::giveMovements(moves, start, station);
	Rook::giveMovements(moves, start, station);
	King::giveMovements(moves, start, station);
	
}
