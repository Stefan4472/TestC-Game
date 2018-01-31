#include "follow_action.h"

void FollowAction::setTarget(Sprite* target)
{
	this->target = target;
}

void FollowAction::init(Sprite* sprite)
{
	
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
			sprite->setDir(dir);
		}
		nextSample += sampleRate;
	}
}