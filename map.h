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

class Map
{

	int TILE_WIDTH = 64;
	int TILE_HEIGHT = 64;
	
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
	
	SDL_Surface* tileImgs[4] = { NULL, NULL, NULL, NULL };
	
	// source and destination rects 
	SDL_Rect src = {0, 0, TILE_WIDTH, TILE_HEIGHT}, dest = {0, 0, TILE_WIDTH, TILE_HEIGHT};

	public:
		// init tile images
		void init(SDL_Surface* grassTileImg, 
				  SDL_Surface* stoneTileImg, 
				  SDL_Surface* obstacleTileImg, 
				  SDL_Surface* waterTileImg);
		// draws background to the given surface/screen
		void drawTo(SDL_Surface* screenSurface);
};

#endif