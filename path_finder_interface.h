#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include <SDL2/SDL.h>
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
		
		// maps point on-screen to point in world coordinates
		virtual SDL_Point screenToWorld(int screenX, int screenY) = 0;
		// maps rect in world coordinates to on-screen coordinates
		virtual SDL_Rect worldToScreen(SDL_Rect worldRect) = 0;
		// returns bounds of tile the given world-coordinate point is in
		virtual SDL_Rect pointToTile(SDL_Point worldPoint) = 0;
		
		// returns coordinates of tile that given point falls on
		//virtual SDL_Point screenPointToMap(int screenX, int screenY) = 0;
		// returns coordinates of tile the given point on the map is on
		//virtual SDL_Rect pointToTile(SDL_Point mapPoint) = 0;
		
		// returns coordinates of tile that the given point falls on 
		//virtual SDL_Point getTileByMapPoint(int x, int y) = 0;
		// returns coordinates of tile that the given SCREEN point falls on
		//virtual SDL_Point getTileByOnsceenPoint(int x, int y) = 0;
		// converts coordinates of tile to 
		//virtual SDL_Rect getTileBounds(int tileX, int tileY) = 0;
};
#endif