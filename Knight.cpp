#pragma once
#include "Knight.h"

void Knight::giveMovements(std::vector<Move>& moves, sf::Vector2i start, Station* station)
{
	sf::Vector2i positions[]{
	sf::Vector2i(start.x + 1, start.y + 2),
	sf::Vector2i(start.x + 1, start.y - 2),
	sf::Vector2i(start.x - 2, start.y + 1),
	sf::Vector2i(start.x - 2, start.y - 1),

	sf::Vector2i(start.x + 2, start.y + 1),
	sf::Vector2i(start.x + 2, start.y - 1),
	sf::Vector2i(start.x - 1, start.y + 2),
	sf::Vector2i(start.x - 1, start.y - 2),
	};

	for (sf::Vector2i& pos : positions) {
		if (isValidPosition(pos, station)) {
			moves.push_back(Move(start, pos, getColor()));
		}
	}

}
