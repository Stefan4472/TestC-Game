#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <cmath>
#include "texture_atlas.h"
#include "sound_atlas.h"
#include "sound.h"
#include "map_chunk.h"
#include "item.h"
#include "attack.h"
#include "consumable.h"
#include "sword.h"
#include "pistol.h"
#include "civilian_sprite.h"
#include "player_sprite.h"
#include "sprite_controller.h"
#include "civilian_sprite_controller.h"
#include "player_sprite_controller.h"
#include "follow_path_action.h"
#include "move_in_dir_action.h"
#include "trigger.h"

// screen dimension constants: todo: read from a universal file
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

class Map // TODO: IMPLEMENTATION OF MAP, AND GAME DRIVER, SHOULD BE SEPARATE.
{	
	// defines the tiles that make up the terrain and map
	MapChunk* mapChunk = NULL;
	
	// virtual coordinates defining view field
	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	
	// source and destination rects 
	SDL_Rect src = {0, 0, TILE_WIDTH, TILE_HEIGHT}, dest = {0, 0, TILE_WIDTH, TILE_HEIGHT};
	
	// pointer to TextureAtlas used for drawing images
	TextureAtlas* textureAtlas = NULL;
	
	// pointer to SoundAtlas used to play sounds
	SoundAtlas* soundAtlas = NULL;
	
	// pointer to player's sprite
	PlayerSpriteController* playerSpriteController = NULL;
	
	// controllers for sprites managed by map
	std::vector<SpriteController*> sprites;
	
	// items generated and managed by map
	std::vector<Item*> items;
	
	// sounds created by sprites, and the map
	std::vector<Sound*> sounds;
	
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
		// init tile images
		void init(PlayerSpriteController* playerSpriteController, TextureAtlas* textureAtlas, SoundAtlas* soundAtlas);
		// advances state by given number of milliseconds
		void update(int ms);
		// adds sprite to list of tracked sprites
		void addControlledSprite(SpriteController* spriteController);
		// adds item to list of items on the map
		void addItem(Item* item);
		// center background to given rect, updating camera
		void centerTo(SDL_Rect center);
		// draws map, sprites, objects. Use center() to center the background to a virtual rectangle
		void drawTo(SDL_Renderer* renderer);
		// returns whether the two rectangles have any intersection
		bool checkCollision(SDL_Rect a, SDL_Rect b);
		// returns an action (list of MoveToActions, each of which define a direction and distance)
		// than a sprite can follow to get from (startX, startY) to (endX, endY)
		FollowPathAction* findPath(float startX, float startY, float endX, float endY);
		// returns an action a sprite can follow that will move it the given number of tiles more or less randomly
		FollowPathAction* findRandomPath(float startX, float startY, int numTiles);
};

#endif