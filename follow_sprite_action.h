#ifndef FOLLOW_ACTION_H
#define FOLLOW_ACTION_H

#include "sprite_action.h"
#include "follow_path_action.h"
#include "sprite.h"
#include "path_finder_interface.h"

// Sprite moves toward target sprite, following it and stopping once it gets within targetRadius
// px of target. Resamples positions based on set RESAMPLE_RATE interval. DOES NOT FINISH! Sprite
// will continue following target indefinitely.

class FollowSpriteAction : public SpriteAction
{
 	// number of milliseconds to wait before re-planning path to target's udpated position
	const int RESAMPLE_RATE = 2000;
	
	// path sprite follows to reach target
	FollowPathAction* path = NULL;
	// time (ms) this action has been going
	int elapsedTime = 0;
	// time next sample should be taken
	int nextSample;
	// sprite to follow
	Sprite* target = NULL;
	// how close to get to the target (px)--squared
	int targetRadiusSquared;
	// whether sprite is close enough to target
	bool closeEnough = false;
	// hook to map, used for navigation
	PathFinder* pathFinder = NULL;
	
	public:
		FollowSpriteAction(PathFinder* pathFinder, Sprite* target, int targetRadius);
		void init(Sprite* sprite);
		bool apply(Sprite* sprite, int ms);
};

#endif