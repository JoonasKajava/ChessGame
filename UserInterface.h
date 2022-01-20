#pragma once
#include "Station.h"
#include "SFML/Graphics.hpp"

class UserInterface {
public:
	UserInterface(Station* _station);
	Station* station;
	void drawBoard(sf::RenderWindow* window);
	void checkPieceClick(sf::RenderWindow* window);
};