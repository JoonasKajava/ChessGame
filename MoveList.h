#pragma once
#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "Station.h"
#include <vector>

class MoveList : public sf::Drawable
{
private:
	sf::RectangleShape _fence;
	sf::Vector2f _position;
	sf::Vector2f _size;
	sf::Text _text;
	sf::Font _font;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	MoveList(sf::Vector2f position, sf::Vector2f size);
	void UpdateString();
	Station* station;

};

