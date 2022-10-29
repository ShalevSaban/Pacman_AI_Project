#include "huntState.h"
#include "EscapeState.h"
#include "CollectingState.h"



huntState::huntState()
{
}


huntState::~huntState()
{
}

void huntState::MakeTransition(Player* owner)
{
	owner->getCurrentState()->OnStateExit(owner); // set the relevant bool flags to false

}

void huntState::OnStateEnter(Player* owner)
{
	owner->setIsHunt(true);
}

void huntState::OnStateExit(Player* owner)
{
	owner->setIsHunt(false);


}
