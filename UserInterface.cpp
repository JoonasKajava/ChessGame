#pragma once
#include "UserInterface.h"
#include <string>
#include <math.h>
#include <list>
#include <set>
#include <algorithm>

UserInterface::UserInterface(Station* _station)
{
	_font.loadFromFile("./Resources/arial.ttf");
	station = _station;

	_turnText.setFont(_font);
	_turnText.setLetterSpacing(1.5f);
	_turnText.setCharacterSize(58);

	_turnText.setOutlineColor(sf::Color::Black);
	_turnText.setOutlineThickness(2.0f);
}

void UserInterface::drawBoard(sf::RenderWindow* window)
{

	sf::Text text;
	text.setFont(_font);
	text.setCharacterSize(64);
	text.setFillColor(sf::Color::Black);

	for (int y = 0; y < 8; y++)
	{
		text.setString(std::to_string(8 - y));
		text.setPosition(sf::Vector2f(50 - (text.getGlobalBounds().width / 2.0f), y * 100));

		window->draw(text);
		for (int x = 0; x < 8; x++)
		{
			sf::RectangleShape square(sf::Vector2f(100, 100));
			if (this->draggedPiece && legalMoves[x][y]) {
				square.setFillColor(sf::Color::Red);
			}
			else {
				square.setFillColor((x + y) % 2 == 0 ? sf::Color(239, 216, 180) : sf::Color(181, 136, 99));
			}
			square.setOutlineColor(sf::Color::Black);
			square.setOutlineThickness(2.0f);
			square.setPosition(sf::Vector2f(x * 100 + 100, y * 100));
			window->draw(square);

			Piece* piece = station->board[y][x];
			if (piece != 0) {
				if (piece->isDragging()) {
					continue;
				}
				piece->getSprite().setPosition(sf::Vector2f(x * 100 + 100, y * 100));
				window->draw(piece->getSprite());
			}

		}
	}

	for (int i = 0; i < 8; i++)
	{
		text.setString(static_cast<char>(97 + i));
		text.setPosition(sf::Vector2f(100 * i + (50 - (text.getGlobalBounds().width / 2.0f)) + 100, 800));
		window->draw(text);
	}

	if (draggedPiece != 0) {
		auto mousepos = sf::Mouse::getPosition(*window);
		sf::Vector2f pos(mousepos.x - 50, mousepos.y - 50);
		draggedPiece->getSprite().setPosition(pos);
		window->draw(draggedPiece->getSprite());
	}

}

void UserInterface::drawStatus(sf::RenderWindow* window)
{
	_turnText.setFillColor(_isWhiteTurn ? sf::Color::White : sf::Color::Black);
	sf::FloatRect bounds = _turnText.getGlobalBounds();

	_turnText.setString(_isWhiteTurn ? "White turn" : "Black turn");
	_turnText.setPosition(sf::Vector2f(900 + (320 / 2.0f - bounds.width / 2.0f), 400 - (bounds.height / 2.0f)));

	window->draw(_turnText);

	window->draw(_blackJail);
	window->draw(_whiteJail);
}

void UserInterface::checkPieceClick(sf::RenderWindow* window)
{
	sf::Vector2i pos = sf::Mouse::getPosition(*window);
	int x = (int)floor(pos.x / 100.0f) - 1;
	int y = (int)floor(pos.y / 100.0f);
	if (x < 0 || x > 7 || y < 0 || y > 7) return;
	sf::Vector2i boardpos(x, y);

	if (!this->draggedPiece) {
		startDrag(boardpos);
	}
	else {
		endDrag(boardpos);
	}
}

void UserInterface::movePiece(sf::Vector2i start, sf::Vector2i end, bool shouldEndTurn)
{
	if (start == end) return;
	Piece* piece = station->board[start.y][start.x];
	station->board[start.y][start.x] = 0;
	Piece* captured = station->board[end.y][end.x];
	if (captured) {
		captured->getColor() ? _whiteJail.addPiece(captured) : _blackJail.addPiece(captured);
	}

	station->board[end.y][end.x] = piece;
	if (shouldEndTurn) _isWhiteTurn = !_isWhiteTurn;
	this->draggedPiece->setMoved(true);

}

void UserInterface::startDrag(sf::Vector2i pos)
{
	if (this->draggedPiece) return;
	Piece* piece = station->board[pos.y][pos.x];
	if (!piece) return;
	if (piece->getColor() != _isWhiteTurn) return;
	piece->setDragging(true);
	this->draggedPiece = piece;
	this->dragStart = pos;

	std::list<Move> moves;
	if (this->draggedPiece) {
		this->draggedPiece->giveMovements(moves, pos, station);
		for (const Move& move : moves) {
			this->legalMoves[move.end.x][move.end.y] = true;
		}
	}

}

void UserInterface::endDrag(sf::Vector2i pos)
{
	if (!this->draggedPiece) return;
	if (!this->legalMoves[pos.x][pos.y] && pos != this->dragStart) return;
	// Do castle
	if (this->draggedPiece->getCode() == KING && abs(dragStart.x - pos.x) > 1) {
		if (pos.x - dragStart.x > 0) {
			movePiece(sf::Vector2i(7, pos.y), sf::Vector2i(5, pos.y), false);
		}
		else {
			movePiece(sf::Vector2i(0, pos.y), sf::Vector2i(3, pos.y), false);
		}
	}


	movePiece(this->dragStart, pos);

	this->draggedPiece->setDragging(false);
	this->draggedPiece = 0;
	for (char y = 0; y < 8; y++) for (char x = 0; x < 8; x++)
	{
		legalMoves[x][y] = 0;
	}

}
