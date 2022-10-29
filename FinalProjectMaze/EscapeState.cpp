#include "EscapeState.h"
#include "CollectingState.h"


const int FX = MSZ - 20; //check this
const int FY = MSZ - 20;


EscapeState::EscapeState()
{
}


EscapeState::~EscapeState()
{
}


void EscapeState::MakeTransition(Player* owner)
{
	owner->getCurrentState()->OnStateExit(owner); // set the relevant bool flags to false
	owner->setCurrentState(new CollectingState());
	owner->getCurrentState()->OnStateEnter(owner); //  set the relevant info

}

void EscapeState::OnStateEnter(Player* owner)
{
	owner->setIsEscaping(true);
	//owner->setDirection(FX, FY);
}

void EscapeState::OnStateExit(Player* owner)
{
	owner->setIsEscaping(false);
	owner->setIsCollecting(true);
}
