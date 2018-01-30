#ifndef IDLE_ACTION_H
#define IDLE_ACTION_H

#include <cmath>
#include "action.h"
#include "sprite.h"

// An idling sprite generally stands still. It can be configured to change direction by setting
// the changeDirInterval to something greater than 0.

class IdleAction:public Action
{
	// length of action (ms)
	int duration;
	// number of ms left in action
	int elapsedTime = 0;
	// how often, if at all, sprite should pick a random direction to change to
	int changeDirInterval = 0;
	// ms since sprite last changed dir
	int msSinceDirChange = 0;
	
	public:
		IdleAction(int ms, int changeDirInterval);
		// stops movement 
		void init(Sprite* sprite);
		// 
		bool apply(Sprite* sprite, int ms);
};

#endif