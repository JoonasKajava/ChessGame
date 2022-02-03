#pragma once
#include "Station.h"
#include "SFML/Graphics.hpp"

class UserInterface {
private:
	Piece* draggedPiece = 0;
	sf::Vector2i dragStart;

	void startDrag(sf::Vector2i pos);
	void endDrag(sf::Vector2i pos);
public:
	bool legalMoves[8][8] = { 0 };
	UserInterface(Station* _station);
	Station* station;
	void drawBoard(sf::RenderWindow* window);
	void checkPieceClick(sf::RenderWindow* window);

	void movePiece(sf::Vector2i start, sf::Vector2i end);

};