#pragma once

#include "MinMaxReturn.h"
#include "Station.h"

struct MiniMaxThreadInput {
public:
	MiniMaxThreadInput(char _depth, Station* _station) : depth(_depth), station(_station) {}

	MinMaxReturn miniMaxReturn;
	char depth;
	Station* station;
};