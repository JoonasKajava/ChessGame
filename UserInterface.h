#pragma once
#include "Station.h"
#include "SFML/Graphics.hpp"
#include "Jail.h"

class UserInterface {
private:
	bool _isWhiteTurn = true;
	sf::Font _font;
	Piece* draggedPiece = 0;
	sf::Vector2i dragStart;

	sf::Text _turnText;

	Jail _whiteJail = Jail(sf::Vector2f(910, 510), sf::Vector2f(300, 300));
	Jail _blackJail = Jail(sf::Vector2f(910, 10), sf::Vector2f(300, 300));

	void startDrag(sf::Vector2i pos);
	void endDrag(sf::Vector2i pos);
public:
	bool legalMoves[8][8] = { 0 };
	UserInterface(Station* _station);
	Station* station;
	void drawBoard(sf::RenderWindow* window);
	void drawStatus(sf::RenderWindow* window);
	void checkPieceClick(sf::RenderWindow* window);

	void movePiece(sf::Vector2i start, sf::Vector2i end, bool shouldEndTurn = true);

};