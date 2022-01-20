#include "UserInterface.h"
#include <string>
#include <math.h>

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

	Piece* draggedPiece = 0;


	for (int y = 0; y < 8; y++)
	{
		text.setString(std::to_string(8 - y));
		text.setPosition(sf::Vector2f(50 - (text.getGlobalBounds().width / 2.0f), y * 100));

		window->draw(text);
		for (int x = 0; x < 8; x++)
		{
			sf::RectangleShape square(sf::Vector2f(100, 100));
			square.setFillColor((x + y) % 2 == 0 ? sf::Color(239, 216, 180) : sf::Color(181, 136, 99));
			square.setPosition(sf::Vector2f(x * 100 + 100, y * 100));
			window->draw(square);

			Piece* piece = station->board[y][x];
			if (piece != 0) {
				if (piece->isDragging()) {
					draggedPiece = piece;
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
	Piece* draggedPiece = 0;
	sf::Vector2i index;
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			Piece* piece = station->board[y][x];
			if (!piece) continue;

			if (piece->isDragging()) {
				draggedPiece = piece;
				piece->setDragging(false);
				index = sf::Vector2i(x, y);
			}
		}
	}
	sf::Vector2i pos = sf::Mouse::getPosition(*window);
	int x = (int)floor(pos.x / 100.0f)-1;
	int y = (int)floor(pos.y / 100.0f);
	if (x < 0 || x > 7 || y < 0 || y > 7) return;

	if (draggedPiece) {
		station->board[index.y][index.x] = 0;
		station->board[y][x] = draggedPiece;
	}
	else {
		Piece* piece = station->board[y][x];
		if (piece != 0) {
			piece->setDragging(true);
		}
	}

}
