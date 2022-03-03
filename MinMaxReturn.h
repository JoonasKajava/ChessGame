#pragma once

#include "Move.h"

class MinMaxReturn {
public:
	MinMaxReturn() : evaluationValue(0) {};
	MinMaxReturn(double value) : evaluationValue(value) {};
	double evaluationValue;
	Move bestMove;
};