#ifndef FOLLOW_ACTION_H
#define FOLLOW_ACTION_H

#include "action.h"
#include "follow_path_action.h"
#include "sprite.h"
#include "path_finder_interface.h"

// Sprite moves toward target sprite, following them. Resamples positions based on set 
// RESAMPLE_RATE interval.

class FollowAction : public Action
{
 	// number of milliseconds to wait before re-planning path to target's udpated position
	const int RESAMPLE_RATE = 2000;
	
	// seed for random number generator
	int seed;
	// path sprite follows to reach target
	FollowPathAction* path = NULL;
	// time (ms) this action has been going
	int elapsedTime = 0;
	// time next sample should be taken
	int nextSample;
	// sprite to follow
	Sprite* target;
	// hook to map, used for navigation
	PathFinder* pathFinder = NULL;
	
	public:
		FollowAction(PathFinder* pathFinder, int randomSeed, Sprite* target, int sampleRate);
		void setTarget(Sprite* target);
		void init(Sprite* sprite);
		bool apply(Sprite* sprite, int ms);
};

#endif