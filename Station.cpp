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

using namespace std;


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

	board[0][0] = std::make_shared<Rook>(Black);
	board[0][1] = std::make_shared<Knight>(Black);
	board[0][2] = std::make_shared<Bishop>(Black);
	board[0][3] = std::make_shared<Queen>(Black);
	board[0][4] = std::make_shared<King>(Black);
	board[0][5] = std::make_shared<Bishop>(Black);
	board[0][6] = std::make_shared<Knight>(Black);
	board[0][7] = std::make_shared<Rook>(Black);


	for (int i = 0; i < 8; i++)
	{
		board[1][i] = std::make_shared<Pawn>(Black);
		board[6][i] = std::make_shared<Pawn>(White);
	}




	board[7][0] = std::make_shared < Rook>(White);
	board[7][1] = std::make_shared < Knight>(White);
	board[7][2] = std::make_shared < Bishop>(White);
	board[7][3] = std::make_shared < Queen>(White);
	board[7][4] = std::make_shared < King>(White);
	board[7][5] = std::make_shared < Bishop>(White);
	board[7][6] = std::make_shared < Knight>(White);
	board[7][7] = std::make_shared < Rook>(White);

	//setupFoolsMate(false);
}

void Station::giveAllLegalMoves(std::vector<Move>& list)
{
	std::vector<Move> tempMoves;
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			Piece* piece = board[y][x].get();
			if (!piece) continue;
			if (piece->getColor() != _isWhiteTurn) continue;
			piece->giveMovements(tempMoves, sf::Vector2i(x, y), this);
		}
	}

	for (Move& move : tempMoves) {
		Station newStation = *this;
		newStation._isMainStation = false;
		newStation.movePiece(move, true);
		if (!newStation.getIsKingInDanger(_isWhiteTurn)) {
			list.push_back(move);
		}
	}
}

void Station::setupFoolsMate(bool forWhite)
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			board[y][x] = nullptr;
		}
	}

	board[0][0] = std::make_shared<Rook>(Black);
	board[0][1] = std::make_shared<Knight>(Black);
	board[0][2] = std::make_shared<Bishop>(Black);
	board[0][3] = std::make_shared<Queen>(Black);
	board[0][4] = std::make_shared<King>(Black);
	board[0][5] = std::make_shared<Bishop>(Black);
	board[0][6] = std::make_shared<Knight>(Black);
	board[0][7] = std::make_shared<Rook>(Black);


	board[1][0] = std::make_shared<Pawn>(Black);
	board[1][1] = std::make_shared<Pawn>(Black);
	board[1][2] = std::make_shared<Pawn>(Black);
	board[1][3] = std::make_shared<Pawn>(Black);
	board[forWhite ? 2 : 1][4] = std::make_shared<Pawn>(Black);
	board[forWhite ? 3 : 2][5] = std::make_shared<Pawn>(Black);
	board[forWhite ? 1 : 3][6] = std::make_shared<Pawn>(Black);
	board[1][7] = std::make_shared<Pawn>(Black);

	board[6][1] = std::make_shared<Pawn>(White);
	board[6][0] = std::make_shared<Pawn>(White);
	board[6][2] = std::make_shared<Pawn>(White);
	board[6][3] = std::make_shared<Pawn>(White);
	board[forWhite ? 6 : 5][4] = std::make_shared<Pawn>(White);
	board[forWhite ? 5 : 6][5] = std::make_shared<Pawn>(White);
	board[forWhite ? 4 : 6][6] = std::make_shared<Pawn>(White);
	board[6][7] = std::make_shared<Pawn>(White);




	board[7][0] = std::make_shared < Rook>(White);
	board[7][1] = std::make_shared < Knight>(White);
	board[7][2] = std::make_shared < Bishop>(White);
	board[7][3] = std::make_shared < Queen>(White);
	board[7][4] = std::make_shared < King>(White);
	board[7][5] = std::make_shared < Bishop>(White);
	board[7][6] = std::make_shared < Knight>(White);
	board[7][7] = std::make_shared < Rook>(White);
}


void Station::movePiece(Move move, bool shouldEndTurn)
{
	if (move.start == move.end) return;

	std::shared_ptr<Piece> piece = board[move.start.y][move.start.x];
	if (!piece) {
		std::cout << "\nTried to move piece that was not found (" << (std::string)(move) << ")\n";
		return;
	}

	if (enPassantBuffer) {
		enPassantBuffer = nullptr;
	}

	if (piece->getCode() == PAWN && abs(move.start.y - move.end.y) == 2) {
		enPassantBuffer = (Pawn*)piece.get();
	}

	if (move.promotion > 0) {

		// TODO: Causes memory leak with the new clause
		switch (move.promotion)
		{
		case QUEEN:
			piece.reset(new Queen(move.isWhite));
			break;
		case ROOK:
			piece.reset(new Rook(move.isWhite));
			break;
		case BISHOP:
			piece.reset(new Bishop(move.isWhite));
			break;
		case KNIGHT:
			piece.reset(new Knight(move.isWhite));
			break;
		default:
			break;
		}
	}

	board[move.start.y][move.start.x] = nullptr;
	std::shared_ptr<Piece> captured = board[move.end.y][move.end.x];
	if (captured) {
		captured->getColor() ? _whiteJail.addPiece(captured) : _blackJail.addPiece(captured);
	}
	if (move.enPassantMove) {
		std::shared_ptr<Piece> captured = board[move.end.y + (move.isWhite ? 1 : -1)][move.end.x];
		if (captured) {
			captured->getColor() ? _whiteJail.addPiece(captured) : _blackJail.addPiece(captured);
		}
		board[move.end.y + (move.isWhite ? 1 : -1)][move.end.x] = nullptr;
	}

	board[move.end.y][move.end.x] = piece;

	if (!piece->getHasBeenMoved(this)) {
		movedPieces.push_back(piece.get());
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
		_isWhiteTurn = !_isWhiteTurn;
		setKingsInDanger();
		if (!_isMainStation) return;

		std::vector<Move> moves;
		this->giveAllLegalMoves(moves);
		if (moves.size() == 0) {
			gameOver = true;
			winner = _isWhiteTurn;
			std::cout << (getIsKingInDanger(_isWhiteTurn) ? "Win!\n" : "Draw!\n");
		}

	}
}

int pieceSquareTable[6][8][8] = {
	// ROOK
	{
	{ 0,  0,  0,  0,  0,  0,  0,  0},
	{5, 10, 10, 10, 10, 10, 10,  5},
	{ -5,  0,  0,  0,  0,  0,  0, -5},
	{-5,  0,  0,  0,  0,  0,  0, -5},
	{-5,  0,  0,  0,  0,  0,  0, -5 },
	{-5,  0,  0,  0,  0,  0,  0, -5},
	{-5,  0,  0,  0,  0,  0,  0, -5},
	{0,  0,  0,  5,  5,  0,  0,  0}
	},

	// KNIGHT
	{
	{-50,-40,-30,-30,-30,-30,-40,-50},
	{-40,-20,  0,  0,  0,  0,-20,-40 },
	{-30,  0, 10, 15, 15, 10,  0,-30},
	{-30,  5, 15, 20, 20, 15,  5,-30},
	{-30,  0, 15, 20, 20, 15,  0,-30},
	{-30,  5, 10, 15, 15, 10,  5,-30},
	{-40,-20,  0,  5,  5,  0,-20,-40},
	{-50,-40,-30,-30,-30,-30,-40,-50}
	},

	// BISHOP
	{
	{-20,-10,-10,-10,-10,-10,-10,-20},
	{-10,  0,  0,  0,  0,  0,  0,-10 },
	{-10,  0,  5, 10, 10,  5,  0,-10},
	{-10,  5,  5, 10, 10,  5,  5,-10},
	{-10,  0, 10, 10, 10, 10,  0,-10},
	{-10, 10, 10, 10, 10, 10, 10,-10},
	{-10,  5,  0,  0,  0,  0,  5,-10},
	{-20,-10,-10,-10,-10,-10,-10,-20},
	},

	// QUEEN
	{
	{-20,-10,-10, -5, -5,-10,-10,-20},
	{-10,  0,  0,  0,  0,  0,  0,-10 },
	{-10,  0,  5,  5,  5,  5,  0,-10},
	{-5,  0,  5,  5,  5,  5,  0, -5},
	{0,  0,  5,  5,  5,  5,  0, -5},
	{-10,  5,  5,  5,  5,  5,  0,-10},
	{-10,  0,  5,  0,  0,  0,  0,-10},
	{-20,-10,-10, -5, -5,-10,-10,-20}
},

// KING
{
	{-30,-40,-40,-50,-50,-40,-40,-30},
	{-30,-40,-40,-50,-50,-40,-40,-30 },
	{-30,-40,-40,-50,-50,-40,-40,-30},
	{-30,-40,-40,-50,-50,-40,-40,-30},
	{-20,-30,-30,-40,-40,-30,-30,-20},
	{-10,-20,-20,-20,-20,-20,-20,-10},
	{20, 20,  0,  0,  0,  0, 20, 20},
	{20, 30, 10,  0,  0, 10, 30, 20}
},

// PAWN
	{
		{0,  0,  0,  0,  0,  0,  0,  0},
	{50, 50, 50, 50, 50, 50, 50, 50 },
	{10, 10, 20, 30, 30, 20, 10, 10},
	{5,  5, 10, 25, 25, 10,  5,  5},
	{0,  0,  0, 20, 20,  0,  0,  0},
	{5, -5,-10,  0,  0,-10, -5,  5},
	{5, 10, 10,-20,-20, 10, 10,  5},
	{0,  0,  0,  0,  0,  0,  0,  0}
}

};


const double pieceValues[6] = {
	500, // ROOK
	320, // KNIGHT
	330, // BISHOP
	900, // QUEEN
	20000, // KING
	100 // PAWN
};

double Station::evaluate()
{
	double evaluation = 0;

	double white = 0;
	double black = 0;

	for (char y = 0; y < 8; y++)
		for (char x = 0; x < 8; x++)
		{
			Piece* piece = board[y][x].get();
			if (!piece) continue;
			std::vector<Move> moves;
			piece->giveMovements(moves, sf::Vector2i(x, y), this);

			double movementFreedomBonus = 0;
			if (piece->getCode() != PAWN) {
				// Pieces get bonus evaluation based on their freedom to move
				movementFreedomBonus = moves.size() * 0.01;
			}
			else {
				// Reward pawns for moving forward
				movementFreedomBonus = (piece->getColor() ? 8 - y : y) * 0.5;
			}

			int pieceSquereValue = pieceSquareTable[piece->getCode()][piece->getColor() ? y : 7 - y][x];
			double value = pieceValues[piece->getCode()] + movementFreedomBonus + pieceSquereValue;

			if (piece->getColor()) {
				white += value;
			}
			else {
				black += value;
			}

		}

	return white-black;
}

int minimaxCounter = 0;

MinMaxReturn Station::miniMax(MinMaxReturn alpha, MinMaxReturn beta, int depth, Station* station, Move _move)
{
	minimaxCounter++;
	MinMaxReturn minMax;

	bool isMax = station->_isWhiteTurn;

	minMax.bestMove = _move;

	std::vector<Move> moves;

	station->giveAllLegalMoves(moves);

	double modifier = station->_isWhiteTurn ? 1 : -1;


	if (moves.size() == 0) {
		
		// Matti
		if (station->getIsKingInDanger(isMax)) {
			minMax.evaluationValue = INFINITY * -modifier;
			std::cout << "eval infinity \n";
		}
		else {
			minMax.evaluationValue = 0;
			std::cout << "eval 0\n";
		}
		return minMax;
	}



	if (depth == 0) {
		minMax.evaluationValue = station->evaluate();
		return minMax;
	}



	Station newStation;

	for (Move& move : moves) {
		newStation = *station;
		newStation._isMainStation = false;
		newStation.movePiece(move);
		MinMaxReturn score = miniMax(alpha, beta, depth - 1, &newStation, move);

		score.bestMove = move;


		if (isMax) {
			if (score.evaluationValue >= beta.evaluationValue) {
				if (!beta.bestMove.isValid()) beta.bestMove = move;
				return beta;
			}
				
			if (score.evaluationValue > alpha.evaluationValue) {
				alpha.bestMove = score.bestMove;
				alpha.evaluationValue = score.evaluationValue;
			}
		}
		else {
			if (score.evaluationValue <= alpha.evaluationValue) {
				if (!alpha.bestMove.isValid()) alpha.bestMove = move;
				return alpha;
			}
			if (score.evaluationValue < beta.evaluationValue) {
				beta.bestMove = score.bestMove;
				beta.evaluationValue = score.evaluationValue;
			}
		}
	}


	return isMax ? alpha : beta;
}

void Station::setKingsInDanger()
{
	_isBlackKingInDanger = false;
	_isWhiteKingInDanger = false;
	sf::Vector2i whiteKing;
	sf::Vector2i blackKing;

	std::vector<Move> whiteMoves;
	std::vector<Move> blackMoves;
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			Piece* piece = board[y][x].get();
			if (!piece) continue;
			if (piece->getCode() == KING) {
				if (piece->getColor()) {
					whiteKing = sf::Vector2i(x, y);
				}
				else {
					blackKing = sf::Vector2i(x, y);
				}
			}
			if (piece->getColor()) {
				piece->giveMovements(whiteMoves, sf::Vector2i(x, y), this);
			}
			else {
				piece->giveMovements(blackMoves, sf::Vector2i(x, y), this);
			}
			
		}
	}
	for (Move& move : whiteMoves) {
		if (move.end == blackKing) {
			_isBlackKingInDanger = true;
		}
	}

	for (Move& move : blackMoves) {
		if (move.end == whiteKing) {
			_isWhiteKingInDanger = true;
		}
	}
}

bool Station::getIsKingInDanger(bool isWhite)
{
	return isWhite ? _isWhiteKingInDanger : _isBlackKingInDanger;
}

std::string Station::getHash()
{
	std::string result = "";
	for (char y = 0; y < 8; y++)
	for (char x = 0; x < 8; x++)
	{
		Piece* piece = board[y][x].get();
		result += piece ? std::to_string(piece->getCode()) : "-";

	}

	return result;
}

