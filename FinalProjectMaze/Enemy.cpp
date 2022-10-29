
#include "GLUT.H"
#include <math.h>
#include <vector>
#include <map>
#include <cmath>
#include <iostream>
#include <time.h>
#include <queue>
#include<string.h>

using namespace std;

#include "Player.h"
#include "Enemy.h"
#include "Cell.h"
#include "consts.h"
#include "huntState.h"
#include "CollectingState.h"
#include "CompareCells.h"
#include "CompareCells.h"

//copy this to emenmy or pacman






Enemy::~Enemy()
{
}



Enemy::Enemy(int x, int y, Player* targetPlayer)
	:Player(x,y,targetPlayer)
{
	type_ = enemy;
	currentState = new huntState();
	currentState->OnStateEnter(this);
}




void Enemy::RestorePath(Cell* pc)
{
	int lastX, lastY;

	if (pc->getParent() != nullptr)
		while (pc->getParent()->getParent() != nullptr)
			pc = pc->getParent();

	if (pc->getParent()!=nullptr)
	{
		 lastX = pc->getParent()->getPoint().getRow();
		 lastY = pc->getParent()->getPoint().getCol();

		setX(pc->getPoint().getRow());
		setY(pc->getPoint().getCol());

		updateLocation(lastX, lastY, type_);
	}



	if ((*maze)[x][y].getIdentity() == PACMAN )
	{
		cout << "Pacman has been eaten, GAME OVER!\n";
		exit(0);
		return;
	}






}

void Enemy::Execute()
{
	EnemyStep();
}



void Enemy::EnemyStep()
{

	int t_row, t_col;
	double h;
	vector <Cell> grays;
	vector <Cell> blacks;
	std::priority_queue<Cell, std::vector<Cell>, CompareCellsF> pq;
	vector<Cell>::iterator it_gray;
	vector<Cell>::iterator it_black;
	Cell* pStart;
	Cell* pCurrent;

	// Setting target location
	t_row = target->getX();
	t_col = target->getY();


	h = CalcDistance(x, y, t_row, t_col);

	pStart = new Cell(x, y, t_row, t_col, h, 0, nullptr);
	// initializes grays and pq
	grays.push_back(*pStart);
	pq.push(*pStart);

	while (!pq.empty())
	{
		pCurrent = new Cell(pq.top());
		pq.pop();
		// If current is actually a target then we stop A*
		if (pCurrent->getPoint().getRow() == t_row && pCurrent->getPoint().getCol() == t_col) // then it is target
		{	//in this case there cannot be a better path to target!!!
			RestorePath(pCurrent);
			return;
		}
		// paint current black
		blacks.push_back(*pCurrent);
		it_gray = find(grays.begin(), grays.end(), *pCurrent);
		if (it_gray != grays.end()) // current was found
			grays.erase(it_gray);

		// now check the neighbors of current
		x = pCurrent->getPoint().getRow();
		y = pCurrent->getPoint().getCol();
		handleNeighbors(pCurrent, pq, grays, blacks);
	} // while
}