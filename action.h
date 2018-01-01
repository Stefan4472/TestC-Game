#ifndef SPRITE_ACTION_H
#define SPRITE_ACTION_H

#include "sprite.h"

// constant indicating action should loop. It will only change if the sprite is interacted with in some way that breaks the current action.
const int ACTION_LOOPING = -1;

class Action
{
	protected:
		// length of action (ms)
		int duration;
		// number of ms left in action
		int timeLeft;
	public:
		// applies the given action to the Sprite over number of milliseconds
		// returns false once the action is completed
		virtual bool apply(Sprite* sprite, int ms)=0; 
		// resets the state of the Action, re-initializing it
		virtual void reset()=0;
};

// action where sprite stands there, unmoving
class IdleAction:public Action
{
	public:
		IdleAction(int ms);
		void init(int ms);
		bool apply(Sprite* sprite, int ms);
		void reset();
};

class WanderAction
{

};

class FollowAction
{

};

class PatrolAction
{

};

class WalkToAction
{

};

class RunAwayAction
{

};

#endif