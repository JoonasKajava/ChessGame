#pragma once
#include "Station.h"
#include "Rook.h"
#include "King.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include <algorithm>
Station::Station(bool createPieces)
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			board[y][x] = nullptr;
		}
	}
	if (!createPieces) return;

	board[0][0] = new Rook(Black);
	board[0][1] = new Knight(Black);
	board[0][2] = new Bishop(Black);
	board[0][3] = new Queen(Black);
	board[0][4] = new King(Black);
	board[0][5] = new Bishop(Black);
	board[0][6] = new Knight(Black);
	board[0][7] = new Rook(Black);


	for (int i = 0; i < 8; i++)
	{
		board[1][i] = new Pawn(Black);
		board[6][i] = new Pawn(White);
	}




	board[7][0] = new Rook(White);
	board[7][1] = new Knight(White);
	board[7][2] = new Bishop(White);
	board[7][3] = new Queen(White);
	board[7][4] = new King(White);
	board[7][5] = new Bishop(White);
	board[7][6] = new Knight(White);
	board[7][7] = new Rook(White);
}

void Station::giveAllLegalMoves(std::list<Move>& list)
{
	sf::Vector2i King;

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			Piece* piece = board[y][x];
			if (!piece) continue;
			if (piece->getColor() != _isWhiteTurn) continue;
			if (piece->getCode() == KING) King = sf::Vector2i(x, y);
			piece->giveMovements(list, sf::Vector2i(x, y), this);
		}
	}

	std::list<Move>::iterator it = list.begin();

	while (it != list.end()) {
		Station newStation = *this;
		newStation.movePiece(*it, false);
		std::list<Move> enemyMovements;
		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				Piece* piece = newStation.board[y][x];
				if (!piece) continue;
				if (piece->getColor() == _isWhiteTurn) continue;
				piece->giveMovements(enemyMovements, sf::Vector2i(x, y), &newStation);
			}
		}
		for (Move& enemyMove : enemyMovements) {
			if (enemyMove.end == King) {
				it = list.erase(it);
			}
		}
		it++;
	}
}


void Station::movePiece(Move move, bool shouldEndTurn)
{
	if (move.start == move.end) return;

	Piece* piece = board[move.start.y][move.start.x];

	if (enPassantBuffer) {
		enPassantBuffer = nullptr;
	}

	if (piece->getCode() == PAWN && abs(move.start.y - move.end.y) == 2) {
		enPassantBuffer = (Pawn*)piece;
	}

	if (move.promotion > 0) {
		delete piece;
		switch (move.promotion)
		{
		case QUEEN:
			piece = new Queen(move.isWhite);
			break;
		case ROOK:
			piece = new Rook(move.isWhite);
			break;
		case BISHOP:
			piece = new Bishop(move.isWhite);
			break;
		case KNIGHT:
			piece = new Knight(move.isWhite);
			break;
		default:
			break;
		}
	}

	board[move.start.y][move.start.x] = 0;
	Piece* captured = board[move.end.y][move.end.x];
	if (captured) {
		captured->getColor() ? _whiteJail.addPiece(captured) : _blackJail.addPiece(captured);
	}
	if (move.enPassantMove) {
		Piece* captured = board[move.end.y + (move.isWhite ? 1 : -1)][move.end.x];
		if (captured) {
			captured->getColor() ? _whiteJail.addPiece(captured) : _blackJail.addPiece(captured);
		}
		board[move.end.y + (move.isWhite ? 1 : -1)][move.end.x] = 0;
	}

	board[move.end.y][move.end.x] = piece;
	if (shouldEndTurn) _isWhiteTurn = !_isWhiteTurn;

	if (!piece->getHasBeenMoved(this)) {
		movedPieces.push_back(piece);
	}

	// Do castle
	if (piece->getCode() == KING && abs(move.start.x - move.end.x) > 1) {
		if (move.end.x - move.start.x > 0) {
			movePiece(Move(sf::Vector2i(7, move.start.y), sf::Vector2i(5, move.start.y), piece->getColor()), false);
		}
		else {
			movePiece(Move(sf::Vector2i(0, move.start.y), sf::Vector2i(3, move.start.y), piece->getColor()), false);
		}
	}
}

const double pieceValues[6] = {
	5, // ROOK
	3, // KNIGHT
	3.25, // BISHOP
	9, // QUEEN
	0, // KING
	1 // PAWN
};

double Station::evaluate()
{
	double evaluation = 0;

	for (char y = 0; y < 8; y++)
		for (char x = 0; x < 8; x++)
		{
			Piece* piece = board[y][x];
			if (!piece) continue;
			evaluation += pieceValues[piece->getCode()] * (!piece->getCode() ? -1 : 1);
		}

	return evaluation;
}

MinMaxReturn Station::max(int depth, Station* station)
{
	MinMaxReturn max;

	if (depth == 0) {
		max.evaluationValue = -station->evaluate();
		return max;
	}

	max.evaluationValue = -INFINITY;

	std::list<Move> moves;

	station->giveAllLegalMoves(moves);

	Station newStation;

	for (Move& move : moves) {
		newStation = *station;
		newStation.movePiece(move);

		MinMaxReturn score = min(depth - 1, &newStation);
		if (score.evaluationValue > max.evaluationValue) {
			max.evaluationValue = score.evaluationValue;
			max.bestMove = move;
		}
	}


	return max;
}

MinMaxReturn Station::min(int depth, Station* station)
{
	MinMaxReturn min;

	if (depth == 0) {
		min.evaluationValue = station->evaluate();
		return min;
	}

	min.evaluationValue = INFINITY;

	std::list<Move> moves;

	Station newStation;

	station->giveAllLegalMoves(moves);

	for (Move& move : moves) {
		newStation = *station;
		newStation.movePiece(move);
		MinMaxReturn score = max(depth - 1, &newStation);
		if (score.evaluationValue < min.evaluationValue) {
			min.evaluationValue = score.evaluationValue;
			min.bestMove = move;
		}
	}

	return min;
}
