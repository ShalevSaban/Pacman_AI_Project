#pragma once
#include <cmath>
class Coin
{
private:
	int row, col;
	double distFromPacman, distFromEnemies;
public:
	Coin();
	Coin(const Coin& other);
	Coin(int r, int c);
	~Coin();
	int getRow() { return row; }
	int getCol() { return col; }
	double getDistanceFromPacman() { return distFromPacman; }
	double getDistanceFromEnemies() { return distFromEnemies; }
	void updateDistanceFromPacman(int prow, int pcol) { distFromPacman = sqrt(pow(row - prow, 2) + pow((col - pcol), 2)); }
	void updateDistanceFromClosestEnemy(int erow, int ecol) { distFromEnemies = sqrt(pow(row - erow, 2) + pow((col - ecol), 2)); }
	bool operator == (const Coin& other) { return other.col == col && other.row == row; }
};

