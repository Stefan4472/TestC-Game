#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <SDL2/SDL.h>

// available id's for tiles
enum TILE_IDS {
	TILE_GRASS,
	TILE_STONE,
	TILE_OBSTACLE,
	TILE_WATER
};

//int TILE_WIDTH = 64;

class Map
{

	int mapRows = 5;
	int mapCols = 5;
	
	// tile grid
	int mapTiles[5][5] = 
	{
		{ TILE_GRASS, TILE_GRASS, TILE_STONE, TILE_STONE, TILE_STONE },
		{ TILE_GRASS, TILE_GRASS, TILE_GRASS, TILE_GRASS, TILE_GRASS },
		{ TILE_GRASS, TILE_GRASS, TILE_OBSTACLE, TILE_STONE, TILE_STONE },
		{ TILE_GRASS, TILE_GRASS, TILE_WATER, TILE_WATER, TILE_STONE },
		{ TILE_GRASS, TILE_GRASS, TILE_WATER, TILE_WATER, TILE_STONE }
	};
	
	// source and destination rects 
	SDL_Rect src = {0, 0, 0, 0}, dest = {0, 0, 0, 0};

	public:
		// draws background to the given surface/screen
		void drawTo(SDL_Surface* screenSurface);
};

#endif