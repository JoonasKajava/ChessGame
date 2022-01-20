#pragma once
#include "SFML/Graphics.hpp";
enum
{
	Rook, Knight, Bishop, Queen, King, Pawn
};

enum { White, Black };

class Piece {
private:
	bool _isWhite;
	unsigned char _code;
	sf::Texture _texture;
	sf::Sprite _sprite;
	bool _isDragging;
public:
	Piece(unsigned char code, bool isWhite);
	Piece() {};
	void setDragging(bool state);
	bool isDragging();
	void setCode(unsigned char code);
	unsigned char getCode();
	unsigned char getColor();
	sf::Sprite& getSprite();
};