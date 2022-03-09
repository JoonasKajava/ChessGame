#pragma once
#include <SFML/Graphics.hpp>
#include "Piece.h"
#include <vector>

class MoveList : public sf::Drawable
{
private:
	sf::RectangleShape _fence;
	sf::Vector2f _position;
	sf::Vector2f _size;
	std::vector<Move> _moves;
	std::vector<std::shared_ptr<Piece>> _pieces;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	MoveList(sf::Vector2f position, sf::Vector2f size);

};

