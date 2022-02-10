#pragma once
#include "King.h"
#include "Station.h"

bool King::canCastle(direction direction, Station* station)
{
    if (this->getHasBeenMoved()) return false;
    bool toLeft = direction == Left;

    int y = this->getColor() ? 7 : 0;
    int index = 4;
    Piece* adPiece = 0;
    do {
        toLeft ? index-- : index++;

        adPiece = station->board[y][index];
    } while (adPiece == 0 && index > 0 && index < 8);
    if (adPiece == 0 || adPiece->getCode() != ROOK || adPiece->getColor() != this->getColor()) return false;
    
	return true;
}

void King::giveMovements(std::list<Move>& moves, sf::Vector2i start, Station* station) {

    for (char y = -1; y <= 1; y++)
    {
        for (char x = -1; x <= 1; x++)
        {
            if (y == 0 && x == 0) continue;
            sf::Vector2i pos(start.x + x, start.y + y);
            if (isValidPosition(pos, station)) {
                moves.push_back(Move(start, pos, getColor()));
            }
        }
    }
    if (typeid(*this) != typeid(King)) return;
    if (canCastle(Left, station)) moves.push_back(Move(start, sf::Vector2i(start.x - 2, start.y), getColor()));
    if (canCastle(Right, station)) moves.push_back(Move(start, sf::Vector2i(start.x + 2, start.y), getColor()));
}

