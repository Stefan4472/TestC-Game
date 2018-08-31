#ifndef SPRITE_ACTION_H
#define SPRITE_ACTION_H

#include <cmath>
#include "game_utils.h"
#include "constants.h"

class Sprite;

// constant indicating action should loop. It will only change if the sprite is interacted with in some way that breaks the current action.
const int ACTION_LOOPING = -1;

// identifiers for the types of actions coded TODO: IS THIS USED?
enum ActionType
{
	ACTION_NO_CHANGE,
	ACTION_IDLE,
	ACTION_WANDER,
	ACTION_FOLLOW,
	ACTION_PATROL,
	ACTION_WALK_TO,
	ACTION_RUN_FROM,
	ACTION_ATTACK,
	ACTION_GAIN_HEALTH,
	ACTION_LOSE_HEALTH,
	NUM_ACTIONS
};

class SpriteAction
{

	public:
		// prepares the sprite to execute the action
		virtual void init(Sprite* sprite) = 0;
		// applies the given action to the Sprite over number of milliseconds
		// returns false once the action is completed
		virtual bool apply(Sprite* sprite, int ms) = 0;
		// called if sprite runs into another sprite
		// default is no change
		virtual void handleSpriteCollision();
		// called if sprite runs into an obstacle on the map
		// default is no change
		virtual void handleMapCollision();
		// resets the state of the Action, re-initializing it
		virtual void reset(); // TODO: NOT SURE IF THIS IS A GOOD IDEA
		~SpriteAction();
};

/*class PatrolAction
{

};

class WalkToAction
{

};

class RunAwayAction
{

};*/

#endif
