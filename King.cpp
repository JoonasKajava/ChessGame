#pragma once
#include "King.h"
#include "Station.h"

bool King::canCastle(direction direction, Station* station)
{
    if (this->getHasBeenMoved(station)) return false;
    bool toLeft = direction == Left;

    int y = this->getColor() ? 7 : 0;
    int index = 4;
    Piece* adPiece = nullptr;
    do {
        toLeft ? index-- : index++;

        adPiece = station->board[y][index];
    } while (adPiece == 0 && index > 1 && index < 7);


    return adPiece != nullptr && adPiece->getCode() == ROOK && !adPiece->getHasBeenMoved(station);
}

void King::giveMovements(std::vector<Move>& moves, sf::Vector2i start, Station* station) {

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

