#include "idle_action.h"

IdleAction::IdleAction(int ms, int changeDirInterval)
{
	duration = ms;	
	elapsedTime = 0;
	this->changeDirInterval = changeDirInterval;
}

void IdleAction::init(Sprite* sprite)
{
	sprite->stopMoving();
}

bool IdleAction::apply(Sprite* sprite, int ms)
{
	elapsedTime += ms;
	msSinceDirChange += ms;

	// check if direction should be changed. If so, pick a random new one
	if (changeDirInterval > 0 && msSinceDirChange > changeDirInterval)
	{
		msSinceDirChange = 0;
		sprite->setDir(rand() % 4 + 1);
	}
	
	// keep going while looping, or elapsed time is less than the specified duration
	return duration == ACTION_LOOPING || elapsedTime < duration;
}