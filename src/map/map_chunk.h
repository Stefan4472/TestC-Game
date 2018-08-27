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
		// number of rows and columns of tiles in the chunk
		static const int TILE_ROWS = 16;
		static const int TILE_COLS = 16;
		// calculated width and height of the chunk, in pixels
		static const int CHUNK_WIDTH = TILE_ROWS * 32; // TODO: DON'T HARDCODE TILE WIDTH/HEIGHT
		static const int CHUNK_HEIGHT = TILE_COLS * 32;

		// returns a new MapChunk with all terrain set to NONE
		static MapChunk getNullChunk();
		// returns a MapChunk with terrain set randomly
		static MapChunk getRandomChunk();

		// terrain tile grid
		MapTerrain const terrain[TILE_ROWS][TILE_COLS];

		void printDebug();

		//std::vector<MapObject> objects;
};
#endif
