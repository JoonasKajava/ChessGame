#include "MoveList.h"


void MoveList::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_fence);

	for (std::shared_ptr<Piece> piece : _pieces) {

	}
}

MoveList::MoveList(sf::Vector2f position, sf::Vector2f size) {
	_fence.setPosition(position);
	_fence.setSize(size);
	_fence.setOutlineColor(sf::Color::Black);
	_fence.setOutlineThickness(2);
	_position = position;
	_size = size;

	_moves = ;
}