#include "action_set.h"

SpriteAction* getInitialAction()
{
	//if (rand() % 2)
	//{
		return new IdleAction(ACTION_LOOPING, 2000);
	//}
	//else 
	//{
	//	return new WanderAction(pathFinder, ACTION_LOOPING, 5, 2000, 10);
	//}
}

SpriteAction* getReaction(SpriteAction* currAction, Trigger* trigger)
{
	printf("Received Trigger type %d\n", trigger->triggerType);
	return currAction;	
}