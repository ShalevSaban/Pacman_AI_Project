#pragma once
#include "Cell.h"
class CompareCellsF
{
public:
	CompareCellsF();
	~CompareCellsF();
	bool operator() (Cell &cl1, Cell &cl2) {
		return cl1.getF() > cl2.getF();
	}
};

