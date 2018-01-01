#include "action.h"

IdleAction::IdleAction(int ms)
{
	duration = ms;	
	timeLeft = ms;
}

void IdleAction::init(int ms)
{
	duration = ms;	
	timeLeft = ms;
}

bool IdleAction::apply(Sprite* sprite, int ms)
{
	// set to no movement
	sprite->movementDir = MOVEMENT_NONE;
	timeLeft -= ms;
	return timeLeft > 0;
}

void IdleAction::reset() 
{
	duration = timeLeft;
}