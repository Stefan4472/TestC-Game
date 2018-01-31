#ifndef FOLLOW_ACTION_H
#define FOLLOW_ACTION_H

#include "action.h"
#include "follow_path_action.h"
#include "sprite.h"

// Sprite moves toward target sprite, following them. Resamples positions based on set 
// RESAMPLE_RATE interval.

class FollowAction : public Action
{
 	// number of milliseconds to wait before re-planning path to target's udpated position
	const int RESAMPLE_RATE = 2000;
	
	// seed for random number generator
	int seed;
	// time next sample should be taken
	int nextSample;
	// current direction  of movement
	int currMovement;
	// sprite to follow
	Sprite* target;
	
	public:
		FollowAction(int randomSeed, Sprite* target, int sampleRate);
		void setTarget(Sprite* target);
		void init(Sprite* sprite);
		bool apply(Sprite* sprite, int ms);
};

#endif