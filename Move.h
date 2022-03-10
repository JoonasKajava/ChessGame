#pragma once
#include "SFML/Graphics.hpp"

class Move {
public:
	Move(sf::Vector2i _start, sf::Vector2i _end, bool _isWhite) {
		this->start = _start;
		this->end = _end;
		this->isWhite = _isWhite;
		this->promotion = -1;
	}
	Move() {};
	sf::Vector2i start;
	sf::Vector2i end;
	bool isWhite;
	bool enPassantMove = false;

	bool operator==(const Move& other) const
	{
		return start == other.start && end == other.end && isWhite == other.isWhite && promotion == other.promotion && enPassantMove == other.enPassantMove;
	}
	char promotion;

	operator std::string() const {
		return static_cast<char>(97 + start.x) + std::to_string(8-start.y) + "-" + static_cast<char>(97 + end.x) + std::to_string(8 - end.y);
	}

	bool isValid() {
		return !(start.x == end.x && start.y == end.y);
	}
};