#pragma once
#include "Rook.h"

void Rook::giveMovements(std::vector<Move>& moves, sf::Vector2i start, Station* station)
{
	for (char i = 0; i < 4; i++)
	{
		char counter = 1;
		bool isValid = false;
		bool shouldStop = false;
		do {
			int x = start.x;
			int y = start.y;
			switch (i)
			{
			case 0:
				x -= counter;
				break;
			case 1:
				y -= counter;
				break;
			case 2:
				x += counter;
				break;
			case 3:
				y += counter;
				break;
			default:
				break;
			}
			sf::Vector2i pos(x, y);
			isValid = isValidPosition(pos, station, shouldStop);
			if (isValid) {
				moves.push_back(Move(start, pos, getColor()));
			}
			
			counter++;
		} while (isValid && !shouldStop);
	}
}
