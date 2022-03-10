#include "MoveList.h"


void MoveList::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_fence);
	target.draw(_text);

}

MoveList::MoveList(sf::Vector2f position, sf::Vector2f size) {
	_fence.setPosition(position);
	_fence.setSize(size);
	_fence.setOutlineColor(sf::Color::Black);
	_fence.setOutlineThickness(2);
	_position = position;
	_size = size;

	_font.loadFromFile("./Resources/arial.ttf");
	_text.setFont(_font);
	_text.setCharacterSize(16);
	_text.setPosition(_position + sf::Vector2f(5, 5));
	_text.setFillColor(sf::Color::Black);
	
}

void MoveList::UpdateString()
{
	std::string moves;

	for (int i = station->_moves.size() - 1; i >= 0; i--) {
		Move& move = station->_moves[i];
		moves += (move.isWhite ? "white " : "black ") + (std::string)move + "\n";
	}

	_text.setString(moves);
}
