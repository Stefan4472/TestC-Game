#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "item.h"
#include "civilian_sprite.h"
#include "player_sprite.h"

// available id's for tiles
enum TILE_IDS 
{ // TODO: TILE_NOTHING
	TILE_BROWN_BRICK,
	TILE_DARK_BRICK,
	TILE_WHITE_BRICK,
	TILE_GRASS,
	TILE_WATER
};

enum OBJECT_IDS // todo: flowers, walkable vs. non-walkable
{
	OBJECT_NOTHING,
	OBJECT_TREE_1,
	OBJECT_TREE_2, 
	OBJECT_ROCK_1,
	OBJECT_ROCK_2, 
	OBJECT_WOODEN_FENCE_LEFT,
	OBJECT_WOODEN_FENCE_POST,
	OBJECT_WOODEN_FENCE_VERT
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
	int mapTiles[10][10] =  // todo: should just be chars
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
	
	int objectTiles[10][10] = 
	{
		{ OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_TREE_1, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING },
		{ OBJECT_WOODEN_FENCE_LEFT, OBJECT_WOODEN_FENCE_LEFT, OBJECT_WOODEN_FENCE_LEFT, OBJECT_WOODEN_FENCE_LEFT, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING },
		{ OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_TREE_2, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING },
		{ OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_WOODEN_FENCE_VERT },
		{ OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_WOODEN_FENCE_VERT },
		{ OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_WOODEN_FENCE_VERT },
		{ OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_WOODEN_FENCE_VERT },
		{ OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_ROCK_1, OBJECT_WOODEN_FENCE_LEFT, OBJECT_WOODEN_FENCE_LEFT, OBJECT_WOODEN_FENCE_LEFT, OBJECT_WOODEN_FENCE_LEFT, OBJECT_WOODEN_FENCE_POST },
		{ OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_ROCK_2, OBJECT_NOTHING, OBJECT_NOTHING },
		{ OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING, OBJECT_NOTHING }
	};
	
	// grid of tiles that are walkable--generated based on mapTiles and objectTiles
	bool walkableTiles[10][10]; 
	
	// images corresponding with TILE_IDS
	SDL_Surface* tileImgs[5] = { NULL, NULL, NULL, NULL, NULL };
	
	// images corresponding with OBJECT_IDS
	SDL_Surface* objectImgs[8] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
	// virtual coordinates view should center on
	SDL_Rect center;
	
	// source and destination rects 
	SDL_Rect src = {0, 0, TILE_WIDTH, TILE_HEIGHT}, dest = {0, 0, TILE_WIDTH, TILE_HEIGHT};
	
	CivilianSprite civilian;
	
	Item pickup;

	public:
		// offsets on x and y that graphics should be drawn to to convert virtual to canvas coordinates
		int viewOffsetX, viewOffsetY;
		// init tile images
		void init(Sprite* playerSprite, SDL_Surface* brown_brick_tile_img, 
				  SDL_Surface* dark_brick_tile_img, 
				  SDL_Surface* white_brick_tile_img, 
				  SDL_Surface* grass_tile_img, 
				  SDL_Surface* water_tile_img,
				  SDL_Surface* tree_1_img,
				  SDL_Surface* tree_2_img,
				  SDL_Surface* rock_1_img,
				  SDL_Surface* rock_2_img,
				  SDL_Surface* wooden_fence_left_img,
				  SDL_Surface* wooden_fence_post,
				  SDL_Surface* wooden_fence_vert,
				  SDL_Surface *civilian_idle_img, 
				  SDL_Surface *civilian_mvup_img,
				  SDL_Surface *civilian_mvdown_img,
				  SDL_Surface *civilian_mvright_img, 
				  SDL_Surface *civilian_mvleft_img,
				  SDL_Surface *pistol_img);
		// advances state by given number of milliseconds
		void update(int ms);
	  	// handles playerSprite on the map. Checks for interactions and calles collision handler if necessary
		void handlePlayer(PlayerSprite* playerSprite);
		// center background to given rect, updating viewOffsetX and viewOffsetY to match
		void centerTo(SDL_Rect newCenter);
		// draws tiled terrain to the given surface/screen. Use center() to center the background to a virtual rectangle
		void drawTerrainTo(SDL_Surface* screenSurface);
		// draws objects to the surface/screen
		void drawObjectsTo(SDL_Surface* screenSurface);
		// draws sprites to the surface/screen
		void drawSpritesTo(SDL_Surface* screenSurface);

};

#endif