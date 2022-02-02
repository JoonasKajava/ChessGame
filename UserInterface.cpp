#pragma once
#include "UserInterface.h"
#include <string>
#include <math.h>
#include <list>
#include <set>
#include <algorithm>

UserInterface::UserInterface(Station* _station)
{
	station = _station;
}

void UserInterface::drawBoard(sf::RenderWindow* window)
{
	sf::Font font;
	font.loadFromFile("./Resources/arial.ttf");

	sf::Text text;
	text.setFont(font);
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

void UserInterface::checkPieceClick(sf::RenderWindow* window)
{
	sf::Vector2i pos = sf::Mouse::getPosition(*window);
	int x = (int)floor(pos.x / 100.0f)-1;
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

void UserInterface::startDrag(sf::Vector2i pos)
{
	if (this->draggedPiece) return;
	Piece* piece = station->board[pos.y][pos.x];
	if (piece != 0) {
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
}

void UserInterface::endDrag(sf::Vector2i pos)
{
	if (!this->draggedPiece) return;
	if (!this->legalMoves[pos.x][pos.y] && pos != this->dragStart) return;
	// Do castle
	if (this->draggedPiece->getCode() == KING && abs(dragStart.x - pos.x) > 1) {
		if (pos.x - dragStart.x > 0) {
			Piece* rook = station->board[pos.y][7];
			rook->setMoved(true);
			station->board[pos.y][5] = rook;
			station->board[pos.y][7] = 0;
		}
		else {
			Piece* rook = station->board[pos.y][0];
			rook->setMoved(true);
			station->board[pos.y][3] = rook;
			station->board[pos.y][0] = 0;
		}
	}
	station->board[this->dragStart.y][this->dragStart.x] = 0;
	station->board[pos.y][pos.x] = this->draggedPiece;
	if (this->dragStart != pos) this->draggedPiece->setMoved(true);
	this->draggedPiece->setDragging(false);
	this->draggedPiece = 0;
	for (char y = 0; y < 8; y++) for (char x = 0; x < 8; x++)
	{
		legalMoves[x][y] = 0;
	}

}
