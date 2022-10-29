#pragma once
#include "State.h"

class EscapeState :
	public State
{
public:
	EscapeState();
	~EscapeState();
	void MakeTransition(Player* owner);
	void OnStateEnter(Player* owner);
	void OnStateExit(Player* owner);

};

