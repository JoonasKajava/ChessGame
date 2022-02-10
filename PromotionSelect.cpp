#pragma once
#include "PromotionSelect.h"
#include "Piece.h"
void PromotionSelect::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_fence);
	for (char i = 0; i < 4; i++)
	{
		target.draw(*_pieces[i]);
	}
	target.draw(_heading);
}

PromotionSelect::PromotionSelect(sf::Vector2f position, sf::Vector2f size)
{
	_position = position;
	_size = size;
	_fence.setPosition(position);
	_fence.setSize(size);
	_fence.setOutlineColor(sf::Color::Black);
	_fence.setOutlineThickness(2);
	_font.loadFromFile("./Resources/arial.ttf");
	_heading.setFont(_font);
	_heading.setString("Promote!");
	_heading.setCharacterSize(48);
	sf::FloatRect bounds = _heading.getGlobalBounds();
	_heading.setPosition(position + sf::Vector2f(size.x / 2.0f - bounds.width / 2.0f, 0));

	_heading.setFillColor(sf::Color::Red);

	char counter = 0;
	for (char code : PROMOTIONS) {
		sf::Texture* texture = new sf::Texture();
		sf::Sprite* sprite = new sf::Sprite();
		texture->loadFromFile("./Resources/Sprites/" + std::to_string(code) + "-0.png");
		sprite->setTexture(*texture);
		sprite->setScale(1.5f, 1.5f);
		sprite->setPosition(position + sf::Vector2f(75*counter, 75));
		_pieces[counter] = sprite;
		counter++;
	}


}

char PromotionSelect::getSelection(sf::Vector2f pos)
{
	for (char i = 0; i < 4; i++)
	{
		sf::Sprite* piece = _pieces[i];
		auto bounds = piece->getGlobalBounds();
		if (bounds.contains(pos)) {

			return i;
		}
	}
	return -1;
}
