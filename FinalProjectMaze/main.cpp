#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <time.h>
#include <math.h>
#include <iostream>

#include "Cell.h"
#include "_room.h"
#include "CompareCells.h"
#include "consts.h"
#include "glut.h"
#include "Player.h"
#include "Enemy.h"
#include "Coin.h"
#include "Pacman.h"


using namespace std;

Cell maze[MSZ][MSZ];	// SPACE is defined 0
Room rooms[NUM_ROOMS]; // An array to hold all the rooms
Pacman* pacman_;
Enemy* enemies[ENEMIES_NUM];
vector <Coin> coins;
vector <Cell> gray;
priority_queue <Coin, vector<Coin>, CompareCoins> pq_coins;



int exisiting_rooms = 0;


Room InitRoom(int roomIndex)
{
	int i, j;
	int width, height, row, col;
	bool overlap = true;
	Room* room = nullptr;

	do
	{
		overlap = false;
		row = 8 + MIN_ROOM_HEIGHT / 2 + rand() % (MSZ - MIN_ROOM_HEIGHT - 16);
		col = 8 + MIN_ROOM_WIDTH / 2 + rand() % (MSZ - MIN_ROOM_WIDTH - 16);

		height = MIN_ROOM_HEIGHT + rand() % 20;	// in the range 8 to 20
		width = MIN_ROOM_WIDTH + rand() % 20;	// in the range 8 to 20

		room = new Room(row, col, width, height);

		Point leftop = room->getLeftTop();
		Point rightbottom = room->getRightBottom();



		// Verify the room is not overlapping another exisiting room
		for (j = 0; j < exisiting_rooms && !overlap; j++)
		{
			if (rooms[j].IsOverlap(room))
				overlap = true;
		}
	} while (overlap);

	/* Initalize room - Fill room with spaces */
	for (i = room->getLeftTop().getRow(); i <= room->getRightBottom().getRow(); i++) {
		for (j = room->getLeftTop().getCol(); j <= room->getRightBottom().getCol(); j++) {
			maze[i][j].setIdentity(SPACE);
		}
	}
	return *room;
}

void DigPath(Cell*& pcurrent, Point& start)
{
	while (!(pcurrent->getPoint() == start))
	{
		maze[pcurrent->getPoint().getRow()][pcurrent->getPoint().getCol()].setIdentity(SPACE);
		pcurrent = pcurrent->getParent();
	}
}

void AddCell(int row, int col, Cell* parent, vector<Cell>& grays, vector<Cell>& blacks,
	priority_queue <Cell*, vector<Cell*>, CompareCells>& pq)
{
	Point p;
	vector<Cell>::iterator it_gray;
	vector<Cell>::iterator it_black;
	Cell* pc;
	double space = 0;

	p.setRow(row);
	p.setCol(col);

	if (maze[row][col].getIdentity() == WALL)
		space = 3;
	else if (maze[row][col].getIdentity() == SPACE)
		space = 0.1;

	pc = new Cell(p, parent->getTarget(), maze[p.getRow()][p.getCol()].getIdentity(), parent->getG() + space, parent);

	it_black = find(blacks.begin(), blacks.end(), *pc);
	it_gray = find(grays.begin(), grays.end(), *pc);

	if (it_gray == grays.end() && it_black == blacks.end()) // it is not black and not gray!
	{
		pq.push(pc);
		grays.push_back(*pc);
	}
}



void CheckNeighbours(Cell* point_neighbour, vector<Cell>& grays, vector<Cell>& blacks,
	priority_queue <Cell*, vector<Cell*>, CompareCells> &pq)
{
	if (point_neighbour->getPoint().getRow() > 0)
		AddCell(point_neighbour->getPoint().getRow() - 1, point_neighbour->getPoint().getCol(), point_neighbour, grays, blacks, pq);
	if (point_neighbour->getPoint().getRow() < MSZ - 1)
		AddCell(point_neighbour->getPoint().getRow() + 1, point_neighbour->getPoint().getCol(), point_neighbour, grays, blacks, pq);
	if (point_neighbour->getPoint().getCol() < MSZ - 1)
		AddCell(point_neighbour->getPoint().getRow(), point_neighbour->getPoint().getCol() + 1, point_neighbour, grays, blacks, pq);
	if (point_neighbour->getPoint().getCol() > 0)
		AddCell(point_neighbour->getPoint().getRow(), point_neighbour->getPoint().getCol() - 1, point_neighbour, grays, blacks, pq);
}



void PaveWay(Point start, Point target)
{
	vector<Cell> grays;
	vector<Cell> blacks;
	priority_queue <Cell*, vector<Cell*>, CompareCells> pq;

	vector<Cell>::iterator it_gray;		// Iterator for drawing grey

	Cell* start_cell;
	Cell* pcurrent;
	bool go_on = false;

	vector<Cell>::iterator it_black;	// Iterator for drawing black

	double wall_cost = 3, space_cost = 0.1;

	// Starting cell is the center of the room at the start point, target cell is the center of the room at the target
	start_cell = new Cell(start, &target, maze[start.getRow()][start.getCol()].getIdentity(), 0, nullptr);

	pq.push(start_cell);
	grays.push_back(*start_cell);

	while (!pq.empty() && !go_on)
	{
		pcurrent = pq.top();	// Pick the best cell
		pq.pop();		// Remove the cell from pq

		// pcurrent can be the TARGET. This is in case when we didn't stop when we first found the target
		// Remove it from grays and paint it black
		if (!(pcurrent->getPoint() == target))
		{
			it_gray = find(grays.begin(), grays.end(), *pcurrent);
			if (it_gray != grays.end())
				grays.erase(it_gray);
			blacks.push_back(*pcurrent);
			// Now check the neighbors
			CheckNeighbours(pcurrent, grays, blacks, pq);
		}
		else
		{
			go_on = true;
			DigPath(pcurrent, start);
			return;
		}
	}
}



/* Creat paths / transitions between the rooms */
void DigTunnels()
{
	int i, j;

	for (i = 0; i < NUM_ROOMS; i++)
	{
		for (j = i+1; j < NUM_ROOMS; j++)
		{
			PaveWay(rooms[i].getCenter(), rooms[j].getCenter());
			cout << "[ROOM " << i << "]" << " Creating Path to Room: " << j << endl;
		}
	}
}


void InitGameSpace() 
{
	int i, j, k;

	// Fill Dugneon with WALLs
	for (i = 0; i < MSZ; i++)
		for (j = 0; j < MSZ; j++)
			maze[i][j].setIdentity(WALL);

	// Create rooms without overlapping
	for (exisiting_rooms = 0; exisiting_rooms < NUM_ROOMS; exisiting_rooms++)
		rooms[exisiting_rooms] = InitRoom(exisiting_rooms);

	DigTunnels();


	for (i = 0; i < MSZ; i++)
		for (j = 0; j < MSZ; j++)
			maze[i][j].setPoint(j, i);


}



void InitPacman()
{
	int x, y;
	do {
		x = rand() % MSZ;
		y = rand() % MSZ;
	} while (maze[x][y].getIdentity() != SPACE);

	pacman_ = new Pacman(x,y,coins);
	maze[x][y].setIdentity(PACMAN);
	pacman_->setCurrentMaze(&maze);
}

void InitEnemies()
{
	int x, y;
	for (int i = 0; i < ENEMIES_NUM; i++)
	{
		do {
			x = rand() % MSZ;
			y = rand() % MSZ;
		} while (maze[x][y].getIdentity() != SPACE);

		
		enemies[i] = new Enemy(x, y,pacman_);
		maze[x][y].setIdentity(ENEMY);
		enemies[i]->setCurrentMaze(&maze);
	}



}

void DeployCoins()
{
	int x, y;
	for (int i = 0; i < COINS_NUM; i++)
	{
		do {
			x = rand() % MSZ;
			y = rand() % MSZ;
		} while (maze[x][y].getIdentity() != SPACE);

		//pacman_ = new Player(pacman, x, y);
		maze[x][y].setIdentity(COIN);
		Coin* c = new Coin(x, y);
		coins.push_back(*c);
	}


	}

//COINS PLACES

void init()
{
	glClearColor(1, 1, 1, 0);// color of window background
	glOrtho(-1, 1, -1, 1, -1, 1);

	srand(time(0));

	InitGameSpace();
	DeployCoins();
	InitPacman();
	InitEnemies();

}



void DrawMaze()
{
	int i, j;
	double xsz = WIDTH / MSZ;
	double ysz = HEIGHT / MSZ;
	double x, y;

	for (i = 0; i < MSZ; i++)
		for (j = 0; j < MSZ; j++)
		{
			switch (maze[i][j].getIdentity()) // Set Cell color
			{
			case SPACE:
				 glColor3d(1, 1, 1);
				break;
			case WALL:
				glColor3d(0.3, 0, 0);	// Dark Red
				break;
			case START:
				glColor3d(0.5, 0.5, 1);		// Cyan
				break;
			case PACMAN:
				glColor3d(255, 255, 0);		// YELLOW
				break;
			case ENEMY:
				glColor3d(0, 0, 255);		// BLUE
				break;
			case COIN:
				glColor3ub(212, 175, 55); //Gold
				break;

			}

			// draw square
			x = 2.0 * (j * xsz) / WIDTH - 1; // value in range [-1,1)
			y = 2.0 * (i * ysz) / HEIGHT - 1; // value in range [-1,1)
			glBegin(GL_POLYGON);
			glVertex2d(x, y);
			glVertex2d(x, y + (2.0 * ysz) / HEIGHT);
			glVertex2d(x + 2.0 * xsz / WIDTH, y + (2.0 * ysz) / HEIGHT);
			glVertex2d(x + 2.0 * xsz / WIDTH, y);
			glEnd();
		}
}




void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer

	DrawMaze();

	glutSwapBuffers();	// show all
}


void ExecutePlayers()
{
	pacman_->Execute();
	
	for (int i = 0; i < ENEMIES_NUM; i++)
		enemies[i]->Execute();
}

void Idle()
{
	ExecutePlayers();
	glutPostRedisplay();
}





void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("Pacmen Game");

	glutDisplayFunc(display);
	glutIdleFunc(Idle);

	init();
	glutMainLoop();
}


