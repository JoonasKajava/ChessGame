#pragma once
#include "Station.h"
#include "SFML/Graphics.hpp"
#include "PromotionSelect.h"
#include "MoveList.h"

class UserInterface {
private:
	sf::Font _font;
	Piece* draggedPiece = 0;
	sf::Vector2i dragStart;

	PromotionSelect _promotionSelect = PromotionSelect(sf::Vector2f(910, 325), sf::Vector2f(300, 150));

	sf::Text _turnText;

	bool promoteBeforeMove = false;
	Move* promotionMove = nullptr;
	MoveList _movesList = MoveList(sf::Vector2f(1250, 5), sf::Vector2f(240, 890));

	void startDrag(sf::Vector2i pos);
	void endDrag(sf::Vector2i pos);
public:
	bool legalMoves[8][8] = { 0 };
	UserInterface(Station* _station);
	Station* station;
	void drawBoard(sf::RenderWindow* window);
	void drawStatus(sf::RenderWindow* window);
	void checkPieceClick(sf::RenderWindow* window);
	void checkPromotionClick(sf::RenderWindow* window);

};