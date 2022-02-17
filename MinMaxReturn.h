#pragma once

#include "Move.h"

class MinMaxReturn {
public:
	MinMaxReturn() {};
	double evaluationValue;
	Move bestMove;
};