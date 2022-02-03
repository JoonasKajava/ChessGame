#pragma once
#include <SFML/Graphics.hpp>
#include "Piece.h"
#include <vector>

class Jail : public sf::Drawable {
private:
	sf::RectangleShape _fence;
	sf::Vector2f _position;
	sf::Vector2f _size;
	std::vector<Piece*> _pieces;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Jail(sf::Vector2f position, sf::Vector2f size);
	void addPiece(Piece* piece);
};