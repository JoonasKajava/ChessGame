#include "Piece.h"
#include <string>

Piece::Piece(unsigned char code, bool isWhite)
{
	_code = code;
	_isWhite = isWhite;
	_texture.loadFromFile("./Resources/Sprites/" + std::to_string(_code) + "-" + std::to_string(_isWhite) + ".png");

	_sprite.setTexture(_texture);
	_sprite.setScale(2, 2);
}

void Piece::setCode(unsigned char code)
{
	_code = code;
}

unsigned char Piece::getCode()
{
	return _code;
}

void Piece::setDragging(bool state)
{
	_isDragging = state;
}

unsigned char Piece::getColor()
{
	return _isWhite;
}

bool Piece::isDragging()
{
	return _isDragging;
}

sf::Sprite& Piece::getSprite()
{
	return _sprite;
}
