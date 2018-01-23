#ifndef MAP_CHUNK_H
#define MAP_CHUNK_H

#include "texture_atlas.h"

// a chunk defines a 16x16 tile section of Map. This includes the tiles for the terrain,
// tile-based objects, pick-ups, and sprites. Chunks have their own coordinate system 
// defining how they fit into the Map as a whole, which works with an x- and y-coordinate.
class MapChunk
{
	public:
		int mapRows = 16;
		int mapCols = 16;

		// tile grid
		char mapTiles[16][16];

		char objectTiles[16][16];

		// grid of tiles that are walkable--generated based on mapTiles and objectTiles
		bool walkableTiles[16][16]; 
		
		MapChunk(int seed);
};
#endif