#pragma once
#include <SFML/Graphics.hpp>
#include "Piece.h"

const char PROMOTIONS [] = { ROOK, KNIGHT, BISHOP, QUEEN };

class PromotionSelect : public sf::Drawable{
private:
	sf::Font _font;
	sf::RectangleShape _fence;
	sf::Vector2f _position;
	sf::Vector2f _size;
	sf::Text _heading;
	sf::Sprite* _pieces[4];
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	PromotionSelect(sf::Vector2f position, sf::Vector2f size);

	char getSelection(sf::Vector2f pos);
};