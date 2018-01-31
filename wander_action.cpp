#include "wander_action.h"

WanderAction::WanderAction(Map* map, int duration, int pathLength, int idleInterval, int randomSeed)  // TODO: MORE RANDOM. LOOK AT MAP AND BLAZE A PATH A FEW TILES LONG
{
	this->map = map;
	this->duration = duration;
	this->pathLength = pathLength;
	seed = randomSeed;
	
	this->idleInterval = idleInterval;
}

void WanderAction::init(Sprite* sprite)
{
	sprite->stopMoving();	
}

bool WanderAction::apply(Sprite* sprite, int ms)
{
	elapsedTime += ms;

	// path exists; move sprite along
	if (currPath)
	{
		// sprite has reached destination
		if (!currPath->apply(sprite, ms)) // TODO: CLEANUP
		{
			delete currPath;
			currPath = NULL;
			sprite->stopMoving();
			msSinceMovement = 0;
		}
	}
	// sprite has idled long enough. Time to get a new path!
	else if (msSinceMovement + ms > idleInterval)
	{
		currPath = map->findRandomPath(sprite->x, sprite->y, pathLength); // TODO: QUERY MAP FOR RANDOM PATH
		currPath->init(sprite);
	}
	else
	{
		msSinceMovement += ms;	
	}
	
	return duration == ACTION_LOOPING || elapsedTime < duration;
}