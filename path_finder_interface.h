#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include "follow_path_action.h"
#include "move_in_dir_action.h"

// The PathFinder is an interface used by SpriteControllers to query a route on the map
// from one point to another in a way that does not traverse invalid tiles.

class PathFinder
{
	public:
		// returns an action (list of MoveToActions, each of which define a direction and distance)
		// than a sprite can follow to get from (startX, startY) to (endX, endY)
		virtual FollowPathAction* findPath(float startX, float startY, float endX, float endY) = 0;
		// returns an action a sprite can follow that will move it the given number of tiles more or less randomly
		virtual FollowPathAction* findRandomPath(float startX, float startY, int numTiles) = 0;
};
#endif