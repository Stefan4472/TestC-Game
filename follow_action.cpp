#include "follow_action.h"

FollowAction::FollowAction(Map* map, int randomSeed, Sprite* target, int sampleRate)
{
	this->map = map;
	seed = randomSeed;
	this->target = target;
	this->sampleRate = sampleRate;
	nextSample = sampleRate;

	// calculate path to follow
	if (target)
	{
		path = map->findPath(sprite->x, sprite->y, target->x, target->y);
	}
}

void FollowAction::setTarget(Sprite* target)
{
	this->target = target;
	
	// delete old path
	if (path)
	{
		delete path;
	}

	path = map->findPath(sprite->x, sprite->y, target->x, target->y);
}

void FollowAction::init(Sprite* sprite)
{
	if (target)
	{
		path.init(sprite);
	}
}

bool FollowAction::apply(Sprite* sprite, int ms) // todo: does it ever complete?
{
	elapsedTime += ms;
	
	// move sprite along current path until it's 32 pixels away or less
	if (path && elapsedTime < nextSample && distSquared(sprite, target) > 1024) 
	{
		path->apply(sprite, ms);
	}
	// re-calculate path if it's time to take another sample
	else if (path)
	{
		delete path;
		
		path = map->findPath(sprite->x, sprite->y, target->x, target->y);
		path->init(sprite);
		
		nextSample += sampleRate;
	}
	
	return true;
}