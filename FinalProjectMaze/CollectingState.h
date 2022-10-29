#pragma once
#include "State.h"

class CollectingState :
	public State
{
public:
	CollectingState();
	~CollectingState();
	void MakeTransition(Player* owner);
	void OnStateEnter(Player* owner);
	void OnStateExit(Player* owner);

};

