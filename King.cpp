#pragma once
#include "King.h"
#include "Station.h"

King::King(bool isWhite) : Piece(KING, isWhite)
{
}

bool King::canCastle(direction direction, Station* station)
{
    if (this->hasBeenMoved) return false;
    bool toLeft = direction == Left;

    int y = this->_isWhite ? 0 : 7;
    int index = 4;
    Piece* adPiece = 0;
    do {
        toLeft ? index-- : index++;

        adPiece = station->board[y][index];
    } while (adPiece == 0 && index > 0 && index < 8);
    if (adPiece == 0 || adPiece->getCode() != ROOK || adPiece->getColor() != this->getColor()) return false;

	return true;
}

void King::giveMovements(std::list<Move>& moves, sf::Vector2i start, Station* station, bool isWhite) {

}

