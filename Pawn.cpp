#pragma once
#include "Pawn.h"

void Pawn::giveMovements(std::list<Move>& moves, sf::Vector2i start, Station* station)
{
	std::list<Move> movesTemp;
	signed char dir = this->getColor() ? -1 : 1;
	sf::Vector2i front1(start.x, start.y + 1 * dir);
	sf::Vector2i front2(start.x, start.y + 2 * dir);
	sf::Vector2i frontLeft(start.x - 1, start.y + 1 * dir);
	sf::Vector2i frontRight(start.x + 1, start.y + 1 * dir);

	if (isValidPosition(front1, station) && !station->board[front1.y][front1.x]) {
		movesTemp.push_back(Move(start, front1, getColor()));
		if (!this->getHasBeenMoved() && !station->board[front2.y][front2.x]) {
			movesTemp.push_back(Move(start, front2, getColor()));
		}
	}
	if (isValidPosition(frontLeft, station)) {
		Piece* FL = station->board[frontLeft.y][frontLeft.x];
		if (FL && FL->getColor() != this->getColor()) movesTemp.push_back(Move(start, frontLeft, getColor()));
	}

	if (isValidPosition(frontRight, station)) {
		Piece* FR = station->board[frontRight.y][frontRight.x];
		if (FR && FR->getColor() != this->getColor()) movesTemp.push_back(Move(start, frontRight, getColor()));
	}

	for (Move& move : movesTemp) {
		givePromotionMovements(movesTemp, &move, station);
	}
	for (Move& move : movesTemp) {
		moves.push_back(move);
	}
	

}
int possiblePromotions[] = {QUEEN, ROOK, BISHOP, KNIGHT};

void Pawn::givePromotionMovements(std::list<Move>& moves, Move* move, Station* station)
{
	int row = _isWhite ? 7 : 0;
	
	if (move->end.y == row) {
		for (int promotion : possiblePromotions) {
			Move promotionMove(move->start, move->end, move->isWhite);
			promotionMove.promotion = promotion;
			moves.push_back(promotionMove);
		}
	}

}
