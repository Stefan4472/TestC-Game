#ifndef MAP_CHUNK_H
#define MAP_CHUNK_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>
#include <cmath>
#include "texture_atlas.h"
#include "map_terrain.h"
#include "map_object.h"
#include "tree_1.h" // TODO: REMOVE THIS IMPORT

using namespace std;

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

		MapChunk();

		// terrain tile grid
		MapTerrain terrain[TILE_ROWS][TILE_COLS];
		// MapObjects present in the chunk
		vector<MapObject*> objects;

		// draws this chunk's terrain (TODO: AND OBJECTS) to the given renderer, with the
		// top-left starting at (x,y)
		void drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas, int x, int y);

		void printDebug();

};
#endif
