#pragma once
#include "SFML/Graphics.hpp";
#include <list>
#include "Move.h"
enum Code
{
	ROOK, KNIGHT, BISHOP, QUEEN, KING, PAWN
};

enum { White, Black };

class Piece {
protected:
	bool _isWhite;
	unsigned char _code;
	sf::Texture _texture;
	sf::Sprite _sprite;
	bool _isDragging;
	
public:
	bool hasBeenMoved;
	Piece(unsigned char code, bool isWhite);
	Piece() {};
	virtual void giveMovements(std::list<Move>& moves, sf::Vector2i start, Station* station, bool isWhite) = 0;
	void setDragging(bool state);
	bool isDragging();
	void setCode(unsigned char code);
	unsigned char getCode();
	unsigned char getColor();
	sf::Sprite& getSprite();
};