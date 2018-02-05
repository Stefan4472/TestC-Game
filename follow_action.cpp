#include "follow_action.h"

FollowAction::FollowAction(PathFinder* pathFinder, int randomSeed, Sprite* target)
{
	printf("Creating FollowAction\n");
	this->pathFinder = pathFinder;
	seed = randomSeed;
	this->target = target;
	nextSample = RESAMPLE_RATE;
}

void FollowAction::setTarget(Sprite* target)
{
	this->target = target;
	
	// delete old path
	if (path)
	{
		delete path;
	}
}

void FollowAction::init(Sprite* sprite)
{
	printf("Initializing Follow on %d\n", sprite);
	if (target)
	{
		printf("Creating path\n");
		path = pathFinder->findPath(sprite->x, sprite->y, target->x, target->y);
		path->init(sprite);
		printf("Finished\n");
	}
	else
	{
		printf("FollowAction has no target set!\n");
	}
}

bool FollowAction::apply(Sprite* sprite, int ms) // todo: does it ever complete? CLEAN UP
{
	printf("Applying Follow on %d\n", sprite);
	
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
		
		path = pathFinder->findPath(sprite->x, sprite->y, target->x, target->y);
		path->init(sprite);
		
		nextSample += RESAMPLE_RATE;
	}
	// no path currently calculated, but target was defined
	else if (target)
	{
		path = pathFinder->findPath(target->x, target->y, target->x, target->y);
		path->init(sprite);
		
		nextSample += RESAMPLE_RATE;
	}
	printf("Finished applying follow on %d\n", sprite);
	
	return true;
}