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
	sf::Vector2i start;
	sf::Vector2i end;
	bool isWhite;
	bool enPassantMove = false;

	bool operator==(const Move& other) const
	{
		return start == other.start && end == other.end && isWhite == other.isWhite && promotion == other.promotion && enPassantMove == other.enPassantMove;
	}
	char promotion;
};