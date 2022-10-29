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
#include "Pacman.h"
#include "Cell.h"
#include "consts.h"
#include "huntState.h"
#include "CollectingState.h"
#include "CompareCells.h"
#include "CompareCoins.h"
#include "Coin.h"

//copy this to emenmy or pacman






Pacman::~Pacman()
{
}


Pacman::Pacman(int x, int y, vector <Coin> &target)
	:Player(x, y),coins(target)
{
	type_ = pacman;
	currentState = new CollectingState();
	currentState->OnStateEnter(this);
	numOfCoins = COINS_NUM;
	distFromEnemy = 22;
}






void Pacman:: CheckBFSNeighbor(vector<Cell*>& grays,int row, int col)
{
	Cell* tempCell = new Cell((*maze)[row][col]);
	if ((*maze)[row][col].getIdentity() == ENEMY)
	{
		bfs_is_running = false;
		closetEnemy = new Point(row, col);
	}
	else
	{
		grays.push_back(tempCell);
	}

}

void Pacman::BfsIteration(vector<Cell*>& grays)
{
	Cell* pcurrent;
	int r, c;

	if (grays.empty())
	{
		bfs_is_running = false;
		resetVisted();
		return;
	}
	else // grays is not empty
	{
		pcurrent = *grays.begin();
		// remove pcurrent from grays and paint it black
		grays.erase(grays.begin());

		r = pcurrent->getPoint().getRow();
		c = pcurrent->getPoint().getCol();
		
		(*maze)[r][c].setVisted(true);
		// add non-visited neighbors
		// up
		if ((*maze)[r + 1][c].getIdentity()!=WALL&& (*maze)[r + 1][c].getVist()==false && bfs_is_running)
			CheckBFSNeighbor(grays,r + 1, c);
		// down
		if ((*maze)[r - 1][c].getIdentity() != WALL && (*maze)[r - 1][c].getVist() == false && bfs_is_running)
			CheckBFSNeighbor(grays, r - 1, c);
		// left
		if ((*maze)[r][c + 1].getIdentity() != WALL && (*maze)[r][c+1].getVist() == false && bfs_is_running)
			CheckBFSNeighbor(grays, r, c - 1);
		// right
		if ((*maze)[r][c - 1].getIdentity() != WALL && (*maze)[r][c-1].getVist() == false && bfs_is_running)
			CheckBFSNeighbor(grays, r, c + 1);
	}

}

void Pacman::resetVisted()
{
	for (int i = 0; i < MSZ; i++)
		for (int j = 0; j < MSZ; j++)
			(*maze)[i][j].setVisted(false);
}

double Pacman::GetDistanceFromPacmanToClosestEnemy()
{
	Point* enemy = getClosetEnemy();
	if (enemy != NULL)
		return CalcDistance(x, y, enemy->getRow(), enemy->getCol());
	else
		return ESCAPE_DISTANCE+1;

}

Point*  Pacman::getClosetEnemy()
{
	bfs_is_running = true;
	vector<Cell*> grays;

	Cell* pc = new Cell((*maze)[x][y]);
	grays.push_back(pc);



	while (bfs_is_running)
		BfsIteration(grays);


	if (!bfs_is_running && closetEnemy)
		return closetEnemy;
}


void Pacman::RestorePacPath(Cell* pc)
{
	if (pc->getParent() != nullptr)
		while (pc->getParent()->getParent() != nullptr)
			pc = pc->getParent();


	//update location
	int lastX = pc->getParent()->getPoint().getRow();
	int lastY = pc->getParent()->getPoint().getCol();

	setX(pc->getPoint().getRow());
	setY(pc->getPoint().getCol());

	

		// Handling coins claim
		if ((*maze)[x][y].getIdentity() == COIN)
		{
			vector<Coin>::iterator it_coin;
			Coin* pCurrent = new Coin(pq_coins.top());
			it_coin = find(coins.begin(), coins.end(), *pCurrent);
			if (it_coin != coins.end()) // current was found
				coins.erase(it_coin);
		
		
			numOfCoins--;
			if (numOfCoins > 0)
				cout << "Great! " << numOfCoins << " more coins left to claim!\n";
		}
	// Handling pacman wins
		if (numOfCoins == 0)
		{
			Sleep(500);
			exit(0);
			return;
		}

		updateLocation(lastX, lastY, type_);

}


void Pacman::ResetCoinsAndRunPQ()
{
	priority_queue <Coin, vector<Coin>, CompareCoins> new_coins_pq;


	for (auto& c : coins)
	{
		c.updateDistanceFromPacman(x,y);
		new_coins_pq.push(c);
	}
	pq_coins = new_coins_pq;
}

void Pacman::PacmanStep()
{

	vector <Cell> grays;
	vector <Cell> blacks;
	priority_queue <Cell, vector<Cell>, CompareCellsF> pq;
	vector<Cell>::iterator it_gray;
	vector<Cell>::iterator it_black;
	Cell* pStart;
	Cell* pCurrent;


			pStart = new Cell(x, y, t_row, t_col, 0, nullptr);
	
		//	// initializes grays and pq
			grays.push_back(*pStart);
			pq.push(*pStart);

			while (!pq.empty())
			{
				pCurrent = new Cell(pq.top());
				pq.pop();
			// If current is actually a target then we stop A*
				if (pCurrent->getPoint().getRow() == t_row && pCurrent->getPoint().getCol() == t_col) // then it is target
				{	//in this case there cannot be a better path to target
					RestorePacPath(pCurrent);
					return;
				}
			// paint current black
				blacks.push_back(*pCurrent);
				it_gray = find(grays.begin(), grays.end(), *pCurrent);
				if (it_gray != grays.end()) // current was found
					grays.erase(it_gray);
	
		//		// now check the neighbors of current
				x = pCurrent->getPoint().getRow();
				y = pCurrent->getPoint().getCol();
	     		handleNeighbors(pCurrent, pq, grays, blacks);
			} 

}


void Pacman::setTarget(int row, int col)
{
	t_row = row;
	t_col = col;
}



Point Pacman::findFarPoint()
{
	int xP = closetEnemy->getRow();
	int yP = closetEnemy->getCol();
	
	int dirY, dirX;
	int newX = x;
	int newY = y;

	if (xP - x > 0)
		dirX = -1;
	else
		dirX = 1;
	if (yP - y > 0)
		dirY = -1;
	else dirY = 1;

	while ((*maze)[newX + dirX][newY].getIdentity() != WALL)
		newX += dirX;
	while ((*maze)[newX][newY+dirY].getIdentity() != WALL)
		newY += dirY;




	
	return new Point(newY,newX);



	
}






void Pacman::Execute()
{
	distFromEnemy = GetDistanceFromPacmanToClosestEnemy();

	ResetCoinsAndRunPQ();
	

	if (isCollecting)
	{
		
		Coin coin_t = pq_coins.top();
		setTarget(coin_t.getRow(), coin_t.getCol());
		PacmanStep();
		if (distFromEnemy < ESCAPE_DISTANCE)
			currentState->MakeTransition(this);
	}
	if (isEscaping)
	{
		Point p_target = findFarPoint();
		setTargetPoint(&p_target);
		PlayerStep();
		///escape operation
		if (distFromEnemy > ESCAPE_DISTANCE)
			currentState->MakeTransition(this);
	}

	

			
}










	



