#ifndef MAP_CHUNK_H
#define MAP_CHUNK_H

#include <stdio.h>
#include <vector>
#include <cmath>
#include "texture_atlas.h"
#include "map_terrain.h"

/*
A chunk defines a 16x16 tile section of Map. This includes the tiles for the terrain,
tile-based objects, pick-ups, and sprites. Chunks have their own coordinate system
defining how they fit into the Map as a whole, which works with an x- and y-coordinate.
TODO: CURRENTLY ONLY HAVE TERRAIN
*/
class MapChunk
{
	public:
		static const int TILE_ROWS = 16;
		static const int TILE_COLS = 16;

		// returns a new MapChunk with all terrain set to NONE
		static MapChunk getNullChunk();
		// returns a MapChunk with terrain set randomly
		static MapChunk getRandomChunk();

		// terrain tile grid
		const MapTerrain terrain[TILE_ROWS][TILE_COLS];

		void printDebug();

		//std::vector<MapObject> objects;
};
#endif
