#pragma once
#include "Piece.h"
#include <string>
#include "Station.h"

Piece::Piece(unsigned char code, bool isWhite)
{
	_code = code;
	_isWhite = isWhite;
	_texture.loadFromFile("./Resources/Sprites/" + std::to_string(_code) + "-" + std::to_string(!_isWhite) + ".png");
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

bool Piece::isValidPosition(sf::Vector2i pos, Station* station, bool& shouldStop)
{
	Piece* piece = station->board[pos.y][pos.x];
	if (pos.x < 0 || pos.x > 7 || pos.y < 0 || pos.y > 7) return false;
	if (piece && piece->getColor() == this->getColor()) return false;
	if (piece && piece->getColor() != this->getColor()) shouldStop = true;
	return true;
}

bool Piece::isValidPosition(sf::Vector2i pos, Station* station)
{
	bool dump;
	return isValidPosition(pos, station, dump);
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

void Piece::setMoved(bool hasBeenMoved)
{
	this->_hasBeenMoved = hasBeenMoved;
}

bool Piece::getHasBeenMoved()
{
	return _hasBeenMoved;
}
