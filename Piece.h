#pragma once
#include "SFML/Graphics.hpp";
#include <list>
#include "Move.h"

class Station;

enum Code
{
	ROOK, KNIGHT, BISHOP, QUEEN, KING, PAWN
};

enum {Black, White };

class Piece {
protected:
	bool _isWhite;
	unsigned char _code;
	sf::Texture _texture;
	sf::Sprite _sprite;
	bool _isDragging = false;
	bool _hasBeenMoved = false;
public:
	
	Piece(unsigned char code, bool isWhite);
	Piece(Piece& other);
	Piece() {};
	virtual void giveMovements(std::list<Move>& moves, sf::Vector2i start, Station* station) = 0;
	bool isValidPosition(sf::Vector2i pos, Station* station, bool& shouldStop);
	bool isValidPosition(sf::Vector2i pos, Station* station);
	void setDragging(bool state);
	bool isDragging();
	void setCode(unsigned char code);
	unsigned char getCode();
	unsigned char getColor();
	sf::Sprite& getSprite();
	void setMoved(bool hasBeenMoved);
	bool getHasBeenMoved();
};