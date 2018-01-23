#ifndef MAP_CHUNK_H
#define MAP_CHUNK_H

#include "texture_atlas.h"
#include <vector>

class MapObject
{
	public:
		MapObject(TextureAtlas* textureAtlas, int textureId, int x, int y);
		int x, y, w, h;
		int textureId;
};

// a chunk defines a 16x16 tile section of Map. This includes the tiles for the terrain,
// tile-based objects, pick-ups, and sprites. Chunks have their own coordinate system 
// defining how they fit into the Map as a whole, which works with an x- and y-coordinate.
class MapChunk
{
	public:
		int mapRows = 24;
		int mapCols = 24;

		// tile grid
		char mapTiles[24][24];

		std::vector<MapObject> objects;

		// grid of tiles that are walkable--generated based on mapTiles and objectTiles
		bool walkableTiles[24][24]; 
		
		// instantiates procedurally-generated chunk, using seed for random number generation
		MapChunk(TextureAtlas* textureAtlas, int seed);
		// loads chunk from given file
		//MapChunk load(
};
#endif