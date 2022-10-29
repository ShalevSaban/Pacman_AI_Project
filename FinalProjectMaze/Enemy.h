#include "Player.h"

class Enemy :public Player
{
public:
	Enemy(int x, int y, Player* targetPlayer);
	~Enemy();
	void EnemyStep();
	void RestorePath(Cell* pc);
	void Execute();


};