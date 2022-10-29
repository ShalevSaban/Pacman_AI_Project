#pragma once

#include "State.h"

class huntState :
	public State
{
public:
	huntState();
	~huntState();
	void MakeTransition(Player* owner);
	void OnStateEnter(Player* owner);
	void OnStateExit(Player* owner);

};

