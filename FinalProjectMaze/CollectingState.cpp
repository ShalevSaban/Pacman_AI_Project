#include "CollectingState.h"
#include "EscapeState.h"


const int FX = MSZ - 20; //check this
const int FY = MSZ - 20;


CollectingState::CollectingState()
{
}


CollectingState::~CollectingState()
{
}

void CollectingState::MakeTransition(Player* owner)
{
	owner->getCurrentState()->OnStateExit(owner); // set the relevant bool flags to false
	owner->setCurrentState(new EscapeState());
	owner->getCurrentState()->OnStateEnter(owner); //  set the relevant info

}

void CollectingState::OnStateEnter(Player* owner)
{
	owner->setIsCollecting(true);
	//owner->setDirection(FX, FY);
}

void CollectingState::OnStateExit(Player* owner)
{
	owner->setIsCollecting(false);


}
