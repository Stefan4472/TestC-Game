#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include "texture_atlas.h"
#include "sound_atlas.h"
#include "item.h"
#include "attack.h"
#include "consumable.h"
#include "weapon.h"
#include "civilian_sprite.h"
#include "player_sprite.h"
#include "trigger.h"

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
		{ TEXTURE_NONE, TEXTURE_NONE, OBJECT_TREE_1, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE },
		{ OBJECT_WOODEN_FENCE_LEFT, OBJECT_WOODEN_FENCE_LEFT, OBJECT_WOODEN_FENCE_LEFT, OBJECT_WOODEN_FENCE_LEFT, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE },
		{ TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, OBJECT_TREE_2, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE },
		{ TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, OBJECT_WOODEN_FENCE_VERT },
		{ TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, OBJECT_WOODEN_FENCE_VERT },
		{ TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, OBJECT_WOODEN_FENCE_VERT },
		{ TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, OBJECT_WOODEN_FENCE_VERT },
		{ TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, OBJECT_ROCK_1, OBJECT_WOODEN_FENCE_LEFT, OBJECT_WOODEN_FENCE_LEFT, OBJECT_WOODEN_FENCE_LEFT, OBJECT_WOODEN_FENCE_LEFT, OBJECT_WOODEN_FENCE_POST },
		{ TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, OBJECT_ROCK_2, TEXTURE_NONE, TEXTURE_NONE },
		{ TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE }
	};
	
	// grid of tiles that are walkable--generated based on mapTiles and objectTiles
	bool walkableTiles[10][10]; 
	
	// virtual coordinates view should center on
	SDL_Rect center;  // todo: replace with camera
	
	// source and destination rects 
	SDL_Rect src = {0, 0, TILE_WIDTH, TILE_HEIGHT}, dest = {0, 0, TILE_WIDTH, TILE_HEIGHT};
	
	// pointer to TextureAtlas used for drawing images
	TextureAtlas* textureAtlas = NULL;
	
	// pointer to SoundAtlas used to play sounds
	SoundAtlas* soundAtlas = NULL;
	
	// sprites generated and managed by map
	std::vector<Sprite*> sprites;
	
	// items generated and managed by map
	std::vector<Item*> items;
	
	// triggers created by sprites that may affect other sprites
	std::vector<Trigger*> triggers;
	
	// handles player request to interact with the map
	void handlePlayerInteract(PlayerSprite* playerSprite);
	
	// returns whether the given region of map is a valid position for a sprite to be.
	// In order to be valid, all four corners must be on walkable tiles.
	bool isValidPosition(SDL_Rect position); // TODO: USAGE OF 4 CALLS TO isWalkable() MAY INTRODUCE OVERHEAD. THIS WILL FOR EACH SPRITE, EACH FRAME
	
	// returns whether the given point is on a "walkable" tile
	bool isWalkable(int x, int y);
	
	public:
		// offsets on x and y that graphics should be drawn to to convert virtual to canvas coordinates
		int viewOffsetX, viewOffsetY;
		// init tile images
		void init(Sprite* playerSprite, TextureAtlas* textureAtlas, SoundAtlas* soundAtlas);
		// advances state by given number of milliseconds
		void update(int ms);
	  	// handles playerSprite on the map. Checks for interactions and calles collision handler if necessary
		void handlePlayer(PlayerSprite* playerSprite);
		// adds sprite to list of tracked sprites
		void addSprite(Sprite* sprite);
		// adds item to list of items on the map
		void addItem(Item* item);
		// center background to given rect, updating viewOffsetX and viewOffsetY to match
		void centerTo(SDL_Rect newCenter);
		// draws tiled terrain to the given surface/screen. Use center() to center the background to a virtual rectangle
		void drawTerrainTo(SDL_Renderer* renderer);
		// draws objects to the surface/screen
		void drawObjectsTo(SDL_Renderer* renderer);
		// draws sprites to the surface/screen
		void drawSpritesTo(SDL_Renderer* renderer);
		// returns whether the two rectangles have any intersection
		bool checkCollision(SDL_Rect a, SDL_Rect b);

};

#endif