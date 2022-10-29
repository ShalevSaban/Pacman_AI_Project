#include "Coin.h"

Coin::Coin()
{
}

Coin::Coin(const Coin& other)
{
	row = other.row;
	col = other.col;
	distFromPacman = other.distFromPacman;
	distFromEnemies = other.distFromEnemies;
}

Coin::Coin(int r, int c)
{
	row = r;
	col = c;
}

Coin::~Coin()
{
}
