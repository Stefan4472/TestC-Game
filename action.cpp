#include "action.h"

void Action::reset()
{
	elapsedTime = 0;
}

Action::~Action()
{
	printf("Deleting Action\n");	
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
	sprite->movementDir = DIRECTION_NONE;
	
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
	//printf("Applying Wander to Sprite. %d ms elapsed, nextChange at %d\n", elapsedTime, nextChange);
	// time to change states
	if (elapsedTime >= nextChange)
	{
		// schedule time for next state change
		nextChange = elapsedTime + (currMovement == DIRECTION_NONE ? wanderInterval : idleInterval);
		// set movement to random direction if it was previously NONE, else stop movement
		currMovement = (currMovement == DIRECTION_NONE ? rand() % 4 : DIRECTION_NONE);
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

bool FollowAction::apply(Sprite* sprite, int ms) // todo: need to return false if completed
{
	elapsedTime += ms;
	// only update if it's time to take another sample
	if (elapsedTime > nextSample) 
	{
		int dir = DIRECTION_NONE;
		int dx = target->x - sprite->x, dy = target->y - sprite->y;
		
		// figure out which direction sprite needs to move 
		if (distSquared(sprite, target) < 100.0f)
		{
			dir = DIRECTION_NONE;
		} 
		else if (dx > 5)
		{
			dir = DIRECTION_RIGHT;
		} 
		else if (dx < -5)
		{
			dir = DIRECTION_LEFT;
		}
		else if (dy > 5)
		{
			dir = DIRECTION_DOWN;
		}
		else if (dy < -5)
		{
			dir = DIRECTION_UP;
		}
		
		// change direction if not correct
		if (currMovement != dir) 
		{
			sprite->changeDir(dir);
		}
		nextSample += sampleRate;
	}
}

HealthRegenAction::HealthRegenAction(int amount, int duration)
{
	amountPerMs = amount / duration;
	printf("Created HealthRegenAction\n");
}

bool HealthRegenAction::apply(Sprite* sprite, int ms)
{
	if (elapsedTime + ms > duration)
	{
		sprite->addHealth((duration - elapsedTime) * amountPerMs); // TODO: DOUBLE CHECK
	} 
	else 
	{
		sprite->addHealth(ms * amountPerMs);	
	}
	elapsedTime += ms;
	return elapsedTime < duration;
}

KnockbackAction::KnockbackAction(int direction)
{
	this->direction = direction;
}
	
bool KnockbackAction::apply(Sprite* sprite, int ms)
{
	// todo: apply over time and use method calls (don't just mess with coordinates)
	switch (direction)  
	{	
		case DIRECTION_RIGHT:
			sprite->x += 32;
			break;
			
		case DIRECTION_LEFT:
			sprite->x -= 32;
			break;
			
		case DIRECTION_UP:
			sprite->y -= 32;
			break;
			
		case DIRECTION_DOWN:
			sprite->y += 32;
			break;
	}
	return false;
}