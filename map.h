#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <SDL2/SDL.h>

// available id's for tiles
enum TILE_IDS {
	TILE_BROWN_BRICK,
	TILE_DARK_BRICK,
	TILE_WHITE_BRICK,
	TILE_GRASS,
	TILE_WATER
};

// screen dimension constants: todo: read from a universal file
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

class Map
{	
	int mapRows = 10;
	int mapCols = 10;
	
	// tile grid
	int mapTiles[10][10] = 
	{
		{ TILE_GRASS, TILE_GRASS, TILE_WHITE_BRICK, TILE_WHITE_BRICK, TILE_WHITE_BRICK, TILE_GRASS, TILE_GRASS, TILE_WHITE_BRICK, TILE_WHITE_BRICK, TILE_WHITE_BRICK },
		{ TILE_GRASS, TILE_GRASS, TILE_GRASS, TILE_GRASS, TILE_GRASS, TILE_GRASS, TILE_GRASS, TILE_WHITE_BRICK, TILE_WHITE_BRICK, TILE_WHITE_BRICK },
		{ TILE_GRASS, TILE_GRASS, TILE_WHITE_BRICK, TILE_WHITE_BRICK, TILE_WHITE_BRICK, TILE_GRASS, TILE_GRASS, TILE_WHITE_BRICK, TILE_WHITE_BRICK, TILE_WHITE_BRICK },
		{ TILE_GRASS, TILE_GRASS, TILE_WATER, TILE_WATER, TILE_WHITE_BRICK, TILE_GRASS, TILE_GRASS, TILE_WHITE_BRICK, TILE_WHITE_BRICK, TILE_WHITE_BRICK },
		{ TILE_GRASS, TILE_GRASS, TILE_WATER, TILE_WATER, TILE_WHITE_BRICK, TILE_GRASS, TILE_GRASS, TILE_WHITE_BRICK, TILE_WHITE_BRICK, TILE_WHITE_BRICK },
		{ TILE_GRASS, TILE_GRASS, TILE_WHITE_BRICK, TILE_WHITE_BRICK, TILE_WHITE_BRICK, TILE_GRASS, TILE_GRASS, TILE_WHITE_BRICK, TILE_WHITE_BRICK, TILE_WHITE_BRICK },
		{ TILE_GRASS, TILE_GRASS, TILE_GRASS, TILE_GRASS, TILE_GRASS, TILE_GRASS, TILE_GRASS, TILE_WHITE_BRICK, TILE_WHITE_BRICK, TILE_WHITE_BRICK },
		{ TILE_GRASS, TILE_GRASS, TILE_WHITE_BRICK, TILE_WHITE_BRICK, TILE_WHITE_BRICK, TILE_GRASS, TILE_GRASS, TILE_WHITE_BRICK, TILE_WHITE_BRICK, TILE_WHITE_BRICK },
		{ TILE_GRASS, TILE_GRASS, TILE_WATER, TILE_WATER, TILE_WHITE_BRICK, TILE_GRASS, TILE_GRASS, TILE_WHITE_BRICK, TILE_WHITE_BRICK, TILE_WHITE_BRICK },
		{ TILE_GRASS, TILE_GRASS, TILE_WATER, TILE_WATER, TILE_WHITE_BRICK, TILE_GRASS, TILE_GRASS, TILE_WHITE_BRICK, TILE_WHITE_BRICK, TILE_WHITE_BRICK }
	};
	
	// images corresponding with TILE_IDS
	SDL_Surface* tileImgs[5] = { NULL, NULL, NULL, NULL, NULL };
	
	// virtual coordinates view should center on
	SDL_Rect center;
	
	// source and destination rects 
	SDL_Rect src = {0, 0, TILE_WIDTH, TILE_HEIGHT}, dest = {0, 0, TILE_WIDTH, TILE_HEIGHT};
	
	public:
		// offsets on x and y that graphics should be drawn to to convert virtual to canvas coordinates
		int viewOffsetX, viewOffsetY;
		// init tile images
		void init(SDL_Surface* brown_brick_tile_img, 
				  SDL_Surface* dark_brick_tile_img, 
				  SDL_Surface* white_brick_tile_img, 
				  SDL_Surface* grass_tile_img, 
				  SDL_Surface* water_tile_img);
		// center background to given rect, updating viewOffsetX and viewOffsetY to match
		void centerTo(SDL_Rect newCenter);
		// draws background to the given surface/screen. Use center() to center the background to a virtual rectangle
		void drawTo(SDL_Surface* screenSurface);
};

#endif