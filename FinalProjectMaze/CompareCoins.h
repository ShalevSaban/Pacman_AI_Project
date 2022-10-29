#pragma once
#include "Coin.h"
class CompareCoins
{
public:
	CompareCoins();
	~CompareCoins();
	bool operator()(Coin& c1, Coin& c2) {
		return c1.getDistanceFromPacman() >
			c2.getDistanceFromPacman();
	}
};

