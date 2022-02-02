#pragma once
#include "Piece.h"

class Station {
public:
	Station();
	//void annaLaillisetSiirrot(std::list<Movements>& list);
	Piece* board[8][8];
};