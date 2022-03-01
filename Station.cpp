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
#include <iostream>
Station::Station(bool createPieces)
{
	_isMainStation = createPieces;
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

void Station::giveAllLegalMoves(std::vector<Move>& list)
{
	std::vector<Move> tempMoves;
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			Piece* piece = board[y][x];
			if (!piece) continue;
			if (piece->getColor() != _isWhiteTurn) continue;
			piece->giveMovements(tempMoves, sf::Vector2i(x, y), this);
		}
	}

	for (Move& move : tempMoves) {
		Station newStation = *this;
		newStation._isMainStation = false;
		newStation.movePiece(move, true);
		if (!newStation.getIsKingInDanger()) {
			list.push_back(move);
		}
	}
}


void Station::movePiece(Move move, bool shouldEndTurn)
{
	if (move.start == move.end) return;

	Piece* piece = board[move.start.y][move.start.x];
	if (!piece) {
		std::cout << "\nTried to move piece that was not found (" << (std::string)(move) << ")\n" ;
		return;
	}

	if (enPassantBuffer) {
		enPassantBuffer = nullptr;
	}

	if (piece->getCode() == PAWN && abs(move.start.y - move.end.y) == 2) {
		enPassantBuffer = (Pawn*)piece;
	}

	if (move.promotion > 0) {

		// TODO: Causes memory leak with the new clause
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

	board[move.start.y][move.start.x] = nullptr;
	Piece* captured = board[move.end.y][move.end.x];
	if (captured) {
		captured->getColor() ? _whiteJail.addPiece(captured) : _blackJail.addPiece(captured);
	}
	if (move.enPassantMove) {
		Piece* captured = board[move.end.y + (move.isWhite ? 1 : -1)][move.end.x];
		if (captured) {
			captured->getColor() ? _whiteJail.addPiece(captured) : _blackJail.addPiece(captured);
		}
		board[move.end.y + (move.isWhite ? 1 : -1)][move.end.x] = nullptr;
	}

	board[move.end.y][move.end.x] = piece;

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
	if (shouldEndTurn) {
		_isKingInDanger = setIsKingInDanger();
		_isWhiteTurn = !_isWhiteTurn;
		if (!_isMainStation) return;

		std::vector<Move> moves;
		this->giveAllLegalMoves(moves);
		if (moves.size() == 0) {
			gameOver = true;
			std::cout << (_isKingInDanger ? "Win!" : "Draw!");
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

	double white = 0;
	double black = 0;

	for (char y = 0; y < 8; y++)
		for (char x = 0; x < 8; x++)
		{
			Piece* piece = board[y][x];
			if (!piece) continue;
			std::vector<Move> moves;
			piece->giveMovements(moves, sf::Vector2i(x, y), this);

			double movementFreedomBonus = 0;
			if (piece->getCode() != PAWN) {
				// Pieces get bonus evaluation based on their freedom to move
				movementFreedomBonus = moves.size() * 0.5;
			}
			else {
				// Reward pawns for moving forward
				movementFreedomBonus = (piece->getColor() ? 8 - y : y);
			}
			double value = (pieceValues[piece->getCode()] + movementFreedomBonus);

			if (piece->getColor()) {
				white = value;
			}
			else {
				black = value;
			}
			
		}

	return _isWhiteTurn ? black-white : white-black;
}

MinMaxReturn Station::miniMax(int depth, Station* station)
{
	MinMaxReturn minMax;

	std::vector<Move> moves;

	station->giveAllLegalMoves(moves);

	double modifier = station->_isWhiteTurn ? 1 : -1;


	if (moves.size() == 0) {

		// Matti
		if (station->getIsKingInDanger()) {
			minMax.evaluationValue = INFINITY * -modifier;
		}
		else {
			minMax.evaluationValue = 0;
		}
		return minMax;
	}



	if (depth == 0) {
		minMax.evaluationValue = station->evaluate();
		return minMax;
	}

	minMax.evaluationValue = INFINITY * modifier;


	Station newStation;

	for (Move& move : moves) {
		newStation = *station;
		newStation._isMainStation = false;
		newStation.movePiece(move);

		MinMaxReturn score = miniMax(depth - 1, &newStation);
		if ((score.evaluationValue > minMax.evaluationValue && !station->_isWhiteTurn) || (score.evaluationValue < minMax.evaluationValue && station->_isWhiteTurn)) {
			minMax.evaluationValue = score.evaluationValue;
			minMax.bestMove = move;
		}
	}


	return minMax;
}

bool Station::setIsKingInDanger()
{
	sf::Vector2i King;

	std::vector<Move> enemyMovements;
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			Piece* piece = board[y][x];
			if (!piece) continue;
			if (piece->getColor() == _isWhiteTurn) {
				if (piece->getCode() == KING) King = sf::Vector2i(x, y);
				continue;
			}
			piece->giveMovements(enemyMovements, sf::Vector2i(x, y), this);
		}
	}
	for (Move& enemyMove : enemyMovements) {
		if (enemyMove.end == King) {
			return true;
		}
	}

	return false;
}

bool Station::getIsKingInDanger()
{
	return _isKingInDanger;
}

