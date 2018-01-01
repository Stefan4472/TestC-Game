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

FollowAction::FollowAction(int randomSeed, Sprite* target, int sampleRate)
{
	seed = randomSeed;
	this->target = target;
	this->sampleRate = sampleRate;
	nextSample = sampleRate;
}

void FollowAction::setTarget(Sprite* target)
{
	this->target = target;
}

bool FollowAction::apply(Sprite* sprite, int ms)
{
	elapsedTime += ms;
	// only update if it's time to take another sample
	if (elapsedTime > nextSample) 
	{
		//printf("Sprite at %f, %f moving to %f, %f\n", sprite->x, sprite->y, target->x, target->y);
		int dir = MOVEMENT_NONE;
		int dx = target->x - sprite->x, dy = target->y - sprite->y;
		// figure out which direction we need to move 
		
		// todo: if abs(dx) < 10, abs(dy) < 10: movement_none
		
		if (sprite->x < target->x)
		{
			//printf("Moving Right\n");
			dir = MOVEMENT_RIGHT;
		} 
		else if (sprite->x > target->x)
		{
			//printf("Moving Left\n");
			dir = MOVEMENT_LEFT;
		}
		else if (sprite->y < target->y)
		{
			//printf("Moving Down\n");
			dir = MOVEMENT_DOWN;
		}
		else if (sprite->y > target->y)
		{
			//printf("Moving Up\n");
			dir = MOVEMENT_UP;
		}
		// change direction if not correct
		if (currMovement != dir) 
		{
			sprite->changeDir(dir);
		}
		nextSample += sampleRate;
	}
}