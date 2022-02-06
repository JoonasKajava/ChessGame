#pragma once
#include "SFML/Graphics.hpp"

class Move {
public:
	Move(sf::Vector2i _start, sf::Vector2i _end, bool _isWhite) {
		this->start = _start;
		this->end = _end;
		this->isWhite = _isWhite;
	}
	sf::Vector2i start;
	sf::Vector2i end;
	bool isWhite;

	bool operator==(const Move& other) const
	{
		return start == other.start && end == other.end && isWhite == other.isWhite;
	}
};