#ifndef SPRITE_ACTION_H
#define SPRITE_ACTION_H

#include <stdlib.h>
#include "sprite.h"

// constant indicating action should loop. It will only change if the sprite is interacted with in some way that breaks the current action.
const int ACTION_LOOPING = -1;

class Action
{
	protected:
		// length of action (ms)
		int duration;
		// number of ms left in action
		int elapsedTime = 0;
	public:
		// applies the given action to the Sprite over number of milliseconds
		// returns false once the action is completed
		virtual bool apply(Sprite* sprite, int ms)=0; 
		// resets the state of the Action, re-initializing it
		virtual void reset();
};

// action where sprite stands there, unmoving
class IdleAction:public Action
{
	public:
		IdleAction(int ms);
		bool apply(Sprite* sprite, int ms);
};

// sprite idles for idleInterval ms, then walks in a random direction for wanderInterval ms
class WanderAction:public Action
{
	// seed for random number generator
	int seed;
	// durations of idling and wandering
	int idleInterval, wanderInterval;
	// time at which next change (wandering<->idling) will occur
	int nextChange;
	// current movement
	int currMovement;
	
	public:
		WanderAction(int durationMs, int randomSeed, int idleInterval, int wanderInterval);
		bool apply(Sprite* sprite, int ms);
};

// sprite moves toward target sprite, following them
class FollowAction:public Action
{
	// seed for random number generator
	int seed;
	// pause between samples of given Sprite's position
	int sampleRate;
	// time next sample should be taken
	int nextSample;
	// current direction  of movement
	int currMovement;
	// sprite to follow
	Sprite* target;
	
	public:
		FollowAction(int randomSeed, Sprite* target, int sampleRate);
		void setTarget(Sprite* target);
		bool apply(Sprite* sprite, int ms);
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