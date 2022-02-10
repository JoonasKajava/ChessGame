#pragma once
#include "SFML/Graphics.hpp"

class Move {
public:
	Move(sf::Vector2i _start, sf::Vector2i _end) {
		this->start = _start;
		this->end = _end;
		this->promotion = 0;
	}
	sf::Vector2i start;
	sf::Vector2i end;
	int promotion;
};