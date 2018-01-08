#include "action_set.h"

Action* getInitialAction()
{
	if (rand() % 2)
	{
		return new IdleAction(ACTION_LOOPING);
	}
	else 
	{
		return new WanderAction(ACTION_LOOPING, 15, 2000, 300);
	}
}

Action* getReaction(Action* currAction, Trigger* trigger)
{
	printf("Received Trigger type %d\n", trigger->triggerType);
	return currAction;	
}