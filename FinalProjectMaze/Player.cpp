
#include "Player.h"
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


#include "Cell.h"
#include "consts.h"
#include "huntState.h"
#include "CollectingState.h"
#include "CompareCells.h"
#include "CompareCells.h"






Player::Player(int x,int y)
{
	isEscaping = false;
	isHunting = false;
	prevIsCoin = false;
	setPoint(x, y);
}


Player::~Player()
{
}


Player::Player(int x,  int y, Player* targetPlayer)
{
	isEscaping = false;
	isCollecting = false;
	isHunting = false;
	prevIsCoin = false;
	setPoint(x, y);
	target = targetPlayer;
}







void Player::updateLocation(int lastX, int lastY, int id)
{
	if ((*maze)[x][y].getIdentity() == COIN)
		prevIsCoin = true;
	else
		prevIsCoin = false;
	if (prevIsCoin)
	{
		if (id == ENEMY)
			(*maze)[lastX][lastY].setIdentity(COIN);
		else
			(*maze)[lastX][lastY].setIdentity(SPACE);
	}
	else
		(*maze)[lastX][lastY].setIdentity(SPACE);


	(*maze)[x][y].setIdentity(id);
}



void Player::UpdatePQ(std::priority_queue <Cell, std::vector<Cell>, CompareCellsF>& pq, Cell* pn)
{
	vector<Cell> tmp;
	Cell tmpCell;
	do
	{
		if (pq.empty())
		{
			cout << "ERROR! PQ is empty in update PQ\n";
			exit(1);
		}
		tmpCell = pq.top();
		pq.pop();
		if (!(tmpCell == (*pn))) // do not copy the Cell we were looking for to tmp!
			tmp.push_back(tmpCell);
	} while (!(tmpCell == (*pn)));
	// now we are out of do-while because we have found the neighbor in PQ. So change it to *pn.
	pq.push(*pn);
	// now push back all the elements that are in tmp
	while (!tmp.empty())
	{
		pq.push(tmp.back());
		tmp.pop_back();
	}
}


double Player::CalcDistance(int row, int col, int t_row, int t_col)
{
	return sqrt(pow(row - t_row, 2) + pow((col - t_col), 2));
}




void Player::CheckNeighbor(Cell* pCurrent, int nrow, int ncol, std::priority_queue<Cell, std::vector<Cell>, CompareCellsF>& pq, vector<Cell>& grays, vector<Cell>& blacks)
{
	double h, g;
	h = CalcDistance(nrow, ncol, pCurrent->getTarget()->getRow(), pCurrent->getTarget()->getCol());	// From target
	g = CalcDistance(nrow, ncol, x, y);	// From current enemy's location
	
	//// this is the neighbor
	Cell* pn = new Cell(nrow, ncol, pCurrent->getTarget()->getRow(), pCurrent->getTarget()->getCol(), h, g, pCurrent);

	//Cell* pn = new Cell(nrow, ncol, pCurrent->getTarget()->getRow(), pCurrent->getTarget()->getCol(),
	//	1, pCurrent);
	//pn->setH(pn->getH());
	vector<Cell>::iterator it_gray;
	vector<Cell>::iterator it_black;

	// check the color of this neighbor
	it_black = find(blacks.begin(), blacks.end(), *pn);
	if (it_black != blacks.end()) // it was found i.e. it is black
		return;
	// white
	it_gray = find(grays.begin(), grays.end(), *pn);
	if (it_gray == grays.end()) // it wasn't found => it is white
	{
		grays.push_back(*pn); // paint it gray
		pq.push(*pn);
	}
	else
		// it is gray
		if (pn->getF() < it_gray->getF()) // then update it (F of neighbor)!!!
		{	// new F			  old F
			// we need to update it in two places:
			// 1. in vector grays
			it_gray->setGVal(pn->getG());
			it_gray->setFVal(pn->getF());
			// 2. in PQ
			// to update a Cell in pq we need to remove it from pq, to update it and to push it back
			UpdatePQ(pq, pn);
		}
}


void Player::handleNeighbors(Cell* pc, std::priority_queue<Cell, std::vector<Cell>, CompareCellsF>& pq, vector<Cell>& grays, vector<Cell>& blacks)
{
	if ((*maze)[x + 1][y].getIdentity() != WALL)	// UP
		CheckNeighbor(pc, x + 1, y, pq, grays, blacks);
	if ((*maze)[x - 1][y].getIdentity() != WALL)	// DOWN
		CheckNeighbor(pc, x - 1, y, pq, grays, blacks);
	if ((*maze)[x][y + 1].getIdentity() != WALL)	// RIGHT
		CheckNeighbor(pc, x, y + 1, pq, grays, blacks);
	if ((*maze)[x][y - 1].getIdentity() != WALL)	// LEFT
		CheckNeighbor(pc, x, y - 1, pq, grays, blacks);
}



void Player::RestorePath(Cell* pc)
{
	int lastX, lastY;

	vector<Cell>:: iterator it_cell;

	if (pc->getParent() != nullptr)
		while (pc->getParent()->getParent() != nullptr)
			pc = pc->getParent();



	if (pc->getParent() != nullptr)
	{
		 lastX = pc->getParent()->getPoint().getRow();
		 lastY = pc->getParent()->getPoint().getCol();

		setX(pc->getPoint().getRow());
		setY(pc->getPoint().getCol());

		updateLocation(lastX, lastY, type_);

		if (lastX == targetPoint->getRow() && lastY == targetPoint->getCol())
		{
			return;
		}

	}
	
}



void Player::PlayerStep()
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
	t_row = targetPoint->getRow();
	t_col = targetPoint->getCol();

	h = CalcDistance(x, y, t_row, t_col);

	pStart = new Cell(x, y, t_row, t_col, h, 0, nullptr);
	

	//pStart = new Cell(x, y, t_row, t_col, 0, nullptr);
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


void Player::setTargetPoint(Point* targetPlayer)
{
	targetPoint = targetPlayer;
}











