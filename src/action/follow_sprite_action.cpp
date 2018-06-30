#include "follow_sprite_action.h"

FollowSpriteAction::FollowSpriteAction(PathFinder* pathFinder, Sprite* target, int targetRadius = 64)
{
	printf("Creating FollowSpriteAction\n");
	this->pathFinder = pathFinder;
	this->target = target;
	targetRadiusSquared = targetRadius * targetRadius;
	nextSample = RESAMPLE_RATE;
	
	if (!target)
	{
		printf("WARNING: FollowSpriteAction has no target set!\n");
	}
}

void FollowSpriteAction::init(Sprite* sprite)
{
	printf("Initializing Follow on %d\n", sprite);
	path = pathFinder->findPath(sprite->x, sprite->y, target->x, target->y);
	path->init(sprite);
	printf("Finished\n");
}

bool FollowSpriteAction::apply(Sprite* sprite, int ms) 
{
	//printf("Applying Follow on %d\n", sprite);
	
	elapsedTime += ms;
	
	// TODO: FIGURE OUT HOW TO GET SPRITE TO STOP WHEN WITHIN TARGETRADIUSSQUARED OF TARGET
	if (!path->apply(sprite, ms) || elapsedTime > nextSample)
	{
		printf("Resampling...\n");
		delete path;
		path = pathFinder->findPath(sprite->x, sprite->y, target->x, target->y);
		path->init(sprite);
		nextSample = elapsedTime + RESAMPLE_RATE;
	}
	
	/*if (distSquared(sprite, target) > targetRadiusSquared)
	{
		
	}
	else
	{
		
	}
	
	// check if sprite is now close enough to stop moving
	if (!closeEnough && distSquared(sprite, target) <= targetRadiusSquared)
	{
		printf("Close enough\n");
		closeEnough = true;	
		sprite->stopMoving();
		delete path;
		path = NULL;
	}
	// check if sprite is no longer close enough, and must calculate a new path
	else if (closeEnough && distSquared(sprite, target) > targetRadiusSquared)
	{
		printf("No longer close enough\n");
		closeEnough = false;
		path = pathFinder->findPath(sprite->x, sprite->y, target->x, target->y);
		path->init(sprite);
		nextSample = elapsedTime + RESAMPLE_RATE;
	}
	// check if it's time to take another sample
	else if (elapsedTime > nextSample)
	{
		printf("Resampling...\n");
		delete path;
		path = pathFinder->findPath(sprite->x, sprite->y, target->x, target->y);
		path->init(sprite);
		nextSample = elapsedTime + RESAMPLE_RATE;
	}
	// no need to change anything, just continue along current path
	else if (!path->apply(sprite, ms))
	{
		printf("Reached end of path.. not sure what to do\n");
		//path->apply(sprite, ms);
	}*/
	//printf("Finished applying follow on %d\n", sprite);
	
	return true;
}