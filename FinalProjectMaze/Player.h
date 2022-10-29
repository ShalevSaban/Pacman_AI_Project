#pragma once

#include <queue>
#include <math.h>
#include <vector>
#include <map>
#include <cmath>
#include <iostream>
#include <string>

#include "State.h"
#include "consts.h"

#include "Cell.h"
#include "Coin.h"
#include "CompareCells.h"
#include "CompareCellsF.h"
#include "CompareCoins.h"


using namespace std;





class State;

const double SPEED = 0.1;

class Player
{
protected:
	State* currentState;
	int x, y,prevColor; // current psition
	double tx, ty; // target
	double dx, dy; // motion direction
	bool isEscaping, isCollecting, isHunting, prevIsCoin;
	int lastMove;
	playerType type_;
	Cell(*maze)[MSZ][MSZ];
	Player* target;
	Point* targetPoint;



public:

	Player(int x,int y, Player* targetPlayer);
	Player(int x, int y);
	~Player();

	//setters
	void setCurrentState(State* pNewState) { currentState = pNewState; }
	void setCurrentMaze(Cell(*array)[MSZ][MSZ]) { maze = array; }
	void setIsEscaping(bool value) { isEscaping = value; }
	void setIsCollecting(bool value) { isCollecting = value; }
	void setIsHunt(bool value) { isHunting = value; }
	void setPoint(int x_, int y_) { x = x_; y = y_; };
	void setLastMove(int move) { lastMove = move; }
	void setTargetPoint(Point* targetPlayer);
	void setX(int x_) { x = x_; };
	void setY(int y_) { y = y_; };


	void updateLocation(int lastX, int lastY, int id);
	void UpdatePQ(std::priority_queue<Cell, std::vector<Cell>, CompareCellsF>& pq, Cell* pn);

	//getters
	int getX() { return x; };
	int getY() { return y; };
	int getLastMove() { return lastMove; }
	State* getCurrentState() { return currentState; }


	double CalcDistance(int row, int col, int t_row, int t_col);
	void CheckNeighbor(Cell* pCurrent, int nrow, int ncol, std::priority_queue<Cell, std::vector<Cell>, CompareCellsF>& pq, vector<Cell>& grays, vector<Cell>& blacks);
	void handleNeighbors(Cell* pc, std::priority_queue<Cell, std::vector<Cell>, CompareCellsF>& pq, vector<Cell>& grays, vector<Cell>& blacks);
	void RestorePath(Cell* pc);
	void PlayerStep();





	




};

