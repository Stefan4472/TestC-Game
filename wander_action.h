#ifndef WANDER_ACTION_H
#define WANDER_ACTION_H

#include "action.h"
#include "follow_path_action.h"
#include "sprite.h"

class Map;

// Sprite idles for idleInterval ms, then queries the map for a random path to follow that is 
// pathLength tiles long. It follows the path, then resumes idling.

class WanderAction:public Action
{
	// seed for random number generator
	int seed;
	// how long (ms) sprite should idle between following paths
	// set to zero to make sprite continually move
	int idleInterval;
	// current path being followed (NULL while idle)
	FollowPathAction* currPath = NULL;
	// length of paths sprite should follow while wandering
	int pathLength = 0;
	// milliseconds since sprite last was following a path/moving
	int msSinceMovement = 0;
	int duration = 0, elapsedTime = 0;
	// map used to find path for the sprite
	Map* map = NULL;
	
	public:
		WanderAction(Map* map, int duration, int pathLength, int idleInterval, int randomSeed);
		void init(Sprite* sprite);
		bool apply(Sprite* sprite, int ms);
};

#endif