#ifndef SPRITE_ACTION_SET
#define SPRITE_ACTION_SET

#include <cmath>
#include "sprite_action.h"
#include "idle_action.h"
#include "wander_action.h"
#include "trigger.h"

// an ActionSet defines the behavior of a sprite class. It provides Actions that control sprites,
// and responses to triggers. So, a computer-controlled sprite will get its actions by querying 
// the ActionSet, and call the ActionSet whenever it receives a trigger.

// The ActionSet is essentially a DFA, where nodes are Actions and paths are Triggers.

// An ActionSet is defined by a 2-dimensional array, where rows are current Actions, and columns
// are received Triggers. The resulting index provides the Action to be taken in result.

// There is generally one action/trigger array defined for each class of Sprite, as a const.

//int CIVILIAN_TRANSITIONS[NUM_ACTIONS][NUM_TRIGGERS] =
//{
							/* TRIGGER_ACTION_FINISHED, TRIGGER_SPRITE_SEEN, TRIGGER_SOUND_HEARD, TRIGGER_ATTACKED, TRIGGER_COLLIDED_WITH */
	/* ACTION_NO_CHANGE   */ //{ ACTION_NO_CHANGE, ACTION_NO_CHANGE, ACTION_NO_CHANGE, ACTION_NO_CHANGE, ACTION_NO_CHANGE },
	/* ACTION_IDLE        */ //{ ACTION_IDLE, 
	/* ACTION_WANDER      */
	/* ACTION_FOLLOW      */
	/* ACTION_PATROL      */
	/* ACTION_WALK_TO     */
	/* ACTION_RUN_FROM    */
	/* ACTION_ATTACK      */
	/* ACTION_GAIN_HEALTH */
	/* ACTION_LOSE_HEALTH */
//};

//class ActionSet
//{
	//int transitions[NUM_ACTIONS][NUM_TRIGGERS];
	
	//public:
SpriteAction* getInitialAction();
SpriteAction* getReaction(SpriteAction* currAction, Trigger* trigger);
//};

#endif