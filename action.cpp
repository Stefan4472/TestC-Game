#include "action.h"

void Action::reset()
{
	elapsedTime = 0;
}

IdleAction::IdleAction(int ms)
{
	duration = ms;	
	elapsedTime = 0;
}

bool IdleAction::apply(Sprite* sprite, int ms)
{
	elapsedTime += ms;
	// set to no movement
	sprite->movementDir = MOVEMENT_NONE;
	
	return duration != ACTION_LOOPING && elapsedTime >= duration;
}

WanderAction::WanderAction(int ms, int randomSeed, int idleInterval, int wanderInterval)
{
	duration = ms;
	elapsedTime = 0;
	seed = randomSeed;
	
	this->idleInterval = idleInterval;
	this->wanderInterval = wanderInterval;
	nextChange = idleInterval;
}

bool WanderAction::apply(Sprite* sprite, int ms)
{
	elapsedTime += ms;
	printf("Applying Wander to Sprite. %d ms elapsed, nextChange at %d\n", elapsedTime, nextChange);
	// time to change states
	if (elapsedTime >= nextChange)
	{
		printf("State change!\n");
		// schedule time for next state change
		nextChange = elapsedTime + (currMovement == MOVEMENT_NONE ? wanderInterval : idleInterval);
		// set movement to random direction if it was previously NONE, else stop movement
		currMovement = (currMovement == MOVEMENT_NONE ? rand() % 4 : MOVEMENT_NONE);
		sprite->changeDir(currMovement);
	}
	sprite->move(ms);
	
	return duration != ACTION_LOOPING && elapsedTime >= duration;
}
