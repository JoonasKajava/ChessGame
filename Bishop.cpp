#pragma once
#include "Bishop.h"

void Bishop::giveMovements(std::list<Move>& moves, sf::Vector2i start, Station* station)
{
	
	for (char i = 0; i < 4; i++)
	{
		int counter = 1;
		sf::Vector2i pos(sf::Vector2i(start.x + (i%2==0 ? counter : -counter), start.y + (i < 2 ? counter : -counter)));
		Piece* slotPiece = station->board[pos.y][pos.x];
		bool shouldStop = false;
		while (isValidPosition(pos, station, shouldStop)) {
			moves.push_back(Move(start, pos));
			if (shouldStop) {
				break;
			}
			counter++;
			pos = sf::Vector2i(sf::Vector2i(start.x + (i % 2 == 0 ? counter : -counter), start.y + (i < 2 ? counter : -counter)));
			slotPiece = station->board[pos.y][pos.x];

		}; 
	}
}
