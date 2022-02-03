#pragma once
#include "Jail.h"


void Jail::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_fence);
	char counter = 0;
	for (Piece* piece : _pieces) {
		sf::Sprite sprite = piece->getSprite();
		sprite.setPosition(_position + sf::Vector2f(75 * (counter % 4), 75 * (counter / 4)));
		sprite.setScale(1.5f, 1.5f);
		target.draw(sprite);
		counter++;
	}

	
}

Jail::Jail(sf::Vector2f position, sf::Vector2f size)
{
	_fence.setPosition(position);
	_fence.setSize(size);
	_fence.setOutlineColor(sf::Color::Black);
	_fence.setOutlineThickness(2);
	_position = position;
	_size = size;
}

void Jail::addPiece(Piece* piece)
{
	_pieces.push_back(piece);
}
