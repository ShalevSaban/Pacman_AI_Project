#include "Player.h"

class Pacman :public Player
{

protected:
	int numOfCoins,t_row,t_col;
	double distFromEnemy,bfs_is_running;
	Point* closetEnemy;
	priority_queue <Coin, vector<Coin>, CompareCoins> pq_coins;
	vector <Coin> &coins;


public:
	Pacman(int x, int y, vector <Coin> &target);
	~Pacman();

	//BFS operations
	void CheckBFSNeighbor(vector<Cell*>& grays, int row, int col);
	void BfsIteration(vector<Cell*>& grays);
	void resetVisted();

	double GetDistanceFromPacmanToClosestEnemy();
	Point* getClosetEnemy();


	void RestorePacPath(Cell* pc);
	void ResetCoinsAndRunPQ();
	void PacmanStep();
	void Execute( );
	void setTarget(int row, int col);
	Point findFarPoint();





};

