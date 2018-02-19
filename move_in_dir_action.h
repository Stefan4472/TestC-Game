#ifndef MOVE_IN_DIR_ACTION
#define MOVE_IN_DIR_ACTION

#include <cmath>
#include "action.h"
#include "sprite.h"

// Moves the sprite in the given direction for the given distane

class MoveInDirAction : public Action
{
	int moveDir = DIRECTION_NONE;
	float remainingDist = 0;
	bool run = false;
	
	public:
		// sets direction and distance. Sprite will run if run = true, otherwise it will walk
		MoveInDirAction(int dir, int distance, bool run);
		// turns sprite in given direction and sets it to start walking/running
		void init(Sprite* sprite);
		// makes sure sprite doesn't overshoot
		bool apply(Sprite* sprite, int ms); 
};

#endif