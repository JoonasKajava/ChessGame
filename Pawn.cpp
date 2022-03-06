#pragma once
#include "Pawn.h"
#include "PromotionSelect.h"

void Pawn::giveMovements(std::vector<Move>& moves, sf::Vector2i start, Station* station)
{
	signed char dir = this->getColor() ? -1 : 1;
	sf::Vector2i front1(start.x, start.y + 1 * dir);
	sf::Vector2i front2(start.x, start.y + 2 * dir);
	sf::Vector2i frontLeft(start.x - 1, start.y + 1 * dir);
	sf::Vector2i frontRight(start.x + 1, start.y + 1 * dir);

	sf::Vector2i left(start.x - 1, start.y);
	sf::Vector2i right(start.x + 1, start.y);

	std::vector<Move> moveTemp;

	if (isValidPosition(left, station)) {
		Pawn* L = static_cast<Pawn*>(station->board[left.y][left.x].get());
		if (L && station->enPassantBuffer == L) {
			Move enPassant(start, frontLeft, getColor());
			enPassant.enPassantMove = true;
			moves.push_back(enPassant);
		}
	}

	if (isValidPosition(right, station)) {
		Pawn* R = static_cast<Pawn*>(station->board[right.y][right.x].get());
		if (R && R == station->enPassantBuffer) {
			Move enPassant(start, frontRight, getColor());
			enPassant.enPassantMove = true;
			moves.push_back(enPassant);
		}
	}

	if (isValidPosition(front1, station) && !station->board[front1.y][front1.x]) {
		moveTemp.push_back(Move(start, front1, getColor()));
		if (!this->getHasBeenMoved(station) && !station->board[front2.y][front2.x]) {
			moves.push_back(Move(start, front2, getColor()));
		}
	}
	if (isValidPosition(frontLeft, station)) {
		Piece* FL = station->board[frontLeft.y][frontLeft.x].get();
		if (FL && FL->getColor() != this->getColor()) moveTemp.push_back(Move(start, frontLeft, getColor()));
	}

	if (isValidPosition(frontRight, station)) {
		Piece* FR = station->board[frontRight.y][frontRight.x].get();
		if (FR && FR->getColor() != this->getColor()) moveTemp.push_back(Move(start, frontRight, getColor()));
	}

	for (Move& move : moveTemp) {
		givePromotionMovements(moves, &move, station);
		moves.push_back(move);
	}


}

void Pawn::givePromotionMovements(std::vector<Move>& moves, Move* move, Station* station)
{
	int row = _isWhite ? 0 : 7;
	
	if (move->end.y == row) {
		for (int promotion : PROMOTIONS) {
			Move promotionMove(move->start, move->end, move->isWhite);
			promotionMove.promotion = promotion;
			moves.push_back(promotionMove);
		}
	}

}