#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <cmath>
#include "texture_atlas.h"
#include "sound_atlas.h"
#include "font_atlas.h"
#include "sound.h"
#include "engine/animation_engine.h"
#include "map_chunk.h"
#include "item_drop.h"
#include "attack.h"
#include "consumable.h"
#include "sword.h"
#include "gun.h"
#include "pistol_ammo.h"
#include "path_finder_interface.h"
#include "sprite_controller.h"
#include "civilian_sprite_controller.h"
#include "player_sprite_controller.h"
#include "follow_path_action.h"
#include "move_in_dir_action.h"

// screen dimension constants: todo: read from a universal file
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

// The Map is the game driver, it tracks and updates game state. It inherits from PathFinder to provide planning methods
// for sprites.

class Map : public PathFinder // TODO: IMPLEMENTATION OF MAP, AND GAME DRIVER, SHOULD BE SEPARATE.
{
	// defines the tiles that make up the terrain and map
	MapChunk* mapChunk = NULL;

	// virtual coordinates defining view field
	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// source and destination rects for drawing
	SDL_Rect src = {0, 0, TILE_WIDTH, TILE_HEIGHT}, dest = {0, 0, TILE_WIDTH, TILE_HEIGHT};

	// renderer used for drawing to screen
	SDL_Renderer* renderer = NULL;

	// pointer to TextureAtlas used for drawing images
	TextureAtlas* textureAtlas = NULL;

	// pointer to SoundAtlas used to play sounds
	SoundAtlas* soundAtlas = NULL;

	// available fonts
	FontAtlas* fontAtlas = NULL;

	// used to create animations
	AnimationEngine* animEngine = NULL;

	// pointer to player's sprite
	PlayerSpriteController* playerSpriteController = NULL;

	// controllers for sprites managed by map
	std::vector<SpriteController*> sprites;

	// item drops generated and managed by map
	std::vector<ItemDrop*> itemDrops;

	// sounds created by sprites, and the map
	std::vector<Sound*> sounds;

	// handles player request to interact with the map
	void handlePlayerInteract(PlayerSpriteController* playerSpriteController);

	// returns whether the given region of map is a valid position for a sprite to be.
	// In order to be valid, all four corners must be on walkable tiles.
	bool isValidPosition(SDL_Rect position); // TODO: USAGE OF 4 CALLS TO isWalkable() MAY INTRODUCE OVERHEAD. THIS WILL FOR EACH SPRITE, EACH FRAME

	// returns whether the given point is on a "walkable" tile
	bool isWalkable(int x, int y);

	public:
		// init tile images
		Map(SDL_Renderer* renderer, TextureAtlas* textureAtlas, SoundAtlas* soundAtlas, FontAtlas* fontAtlas);
		// runs the game
		void run();
		// advances state by given number of milliseconds
		void update(int ms);
		// adds sprite to list of tracked sprites
		void addControlledSprite(SpriteController* spriteController);
		// adds drop to the map
		void addDrop(ItemDrop* itemDrop);
		// center background to given rect, updating camera
		void centerTo(SDL_Rect center);
		// draws map, sprites, objects. Use center() to center the background to a virtual rectangle
		void drawTo(SDL_Renderer* renderer);
		// returns whether the two rectangles have any intersection
		bool checkCollision(SDL_Rect a, SDL_Rect b);

		// creates stack of items with given id and quantity
		ItemStack* createItemStack(int itemId, int quantity);

		// returns an action (list of MoveToActions, each of which define a direction and distance)
		// than a sprite can follow to get from (startX, startY) to (endX, endY)
		FollowPathAction* findPath(float startX, float startY, float endX, float endY);
		// returns an action a sprite can follow that will move it the given number of tiles more or less randomly
		FollowPathAction* findRandomPath(float startX, float startY, int numTiles);
		// maps point on-screen to point in world coordinates
		SDL_Point screenToWorld(int screenX, int screenY);
		// maps rect in world coordinates to on-screen coordinates
		SDL_Rect worldToScreen(SDL_Rect worldRect);
		// returns bounds of tile the given world-coordinate point is in
		SDL_Rect pointToTile(SDL_Point worldPoint);
};

#endif
