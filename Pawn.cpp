#pragma once
#include "Pawn.h"

void Pawn::giveMovements(std::list<Move>& moves, sf::Vector2i start, Station* station)
{
	signed char dir = this->getColor() ? 1 : -1;
	sf::Vector2i front1(start.x, start.y + 1 * dir);
	sf::Vector2i front2(start.x, start.y + 2 * dir);
	sf::Vector2i frontLeft(start.x - 1, start.y + 1 * dir);
	sf::Vector2i frontRight(start.x + 1, start.y + 1 * dir);

	if (!station->board[front1.y][front1.x]) {
		moves.push_back(Move(start, front1));
		if (!this->getHasBeenMoved() && !station->board[front2.y][front2.x]) {
			moves.push_back(Move(start, front2));
		}
	}
	Piece* FL = station->board[frontLeft.y][frontLeft.x];
	if (FL && FL->getColor() != this->getColor()) moves.push_back(Move(start, frontLeft));

	Piece* FR = station->board[frontRight.y][frontRight.x];
	if (FR && FR->getColor() != this->getColor()) moves.push_back(Move(start, frontRight));

}
