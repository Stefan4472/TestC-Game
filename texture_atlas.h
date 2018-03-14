#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include <SDL2/SDL.h>

// provides access to graphics via a single tile "atlas"
// all used graphics are placed in a single image. Individual images are retrieved
// via subimaging the full atlas with a pre-determined, known SDL_Rect

// the Textures enum defines the graphics that may be used.
// the TextureRegions array defines the bounds of the corresponding textures in the atlas

// note: this animations were not implemented.
// the Animations enum defines the animations that are known
// the AnimationFrames array defines the corresponding Textures that make up the animation

// call draw(textureId, ...) functions to draw the desired texture to the screen

enum Textures 
{
	TEXTURE_NONE,
	TILE_GRASS,
	TILE_BROWN_BRICK,
	TILE_DARK_BRICK,
	TILE_WHITE_BRICK,
	TILE_WATER,
	OBJECT_TREE_1,
	OBJECT_TREE_2, 
	OBJECT_ROCK_1,
	OBJECT_ROCK_2, 
	OBJECT_WOODEN_FENCE_LEFT,
	OBJECT_WOODEN_FENCE_POST,
	OBJECT_WOODEN_FENCE_VERT,
	//CIVILIAN_IDLE,
	CIVILIAN_IDLE_RIGHT,
	CIVILIAN_IDLE_LEFT,
	CIVILIAN_IDLE_UP,
	CIVILIAN_IDLE_DOWN,
	CIVILIAN_WALK_RIGHT,
	CIVILIAN_WALK_LEFT,
	CIVILIAN_WALK_UP,
	CIVILIAN_WALK_DOWN,
	CIVILIAN_RUN_RIGHT,
	CIVILIAN_RUN_LEFT,
	CIVILIAN_RUN_UP,
	CIVILIAN_RUN_DOWN,
	PLAYER_IDLE_RIGHT,
	PLAYER_IDLE_LEFT,
	PLAYER_IDLE_UP,
	PLAYER_IDLE_DOWN,
	PLAYER_WALK_RIGHT,
	PLAYER_WALK_LEFT,
	PLAYER_WALK_UP,
	PLAYER_WALK_DOWN,
	PLAYER_RUN_RIGHT,
	PLAYER_RUN_LEFT,
	PLAYER_RUN_UP,
	PLAYER_RUN_DOWN,
	OBJECT_PISTOL_1,
	BREAD_LOAF,
	CHICKEN_LEG,
	BEER_MUG,
	SWORD_1,
	POTION_GREEN,
	SCROLL_1,
	MOVING_BULLET,
	TEXTURE_PISTOL_AMMO,
	TEXTURE_SHOTGUN_AMMO,
	TEXTURE_RIFLE_AMMO
};

const SDL_Rect textureRegions[48] = 
{
	SDL_Rect { 0, 0, 0, 0 }, // todo: don't allow texture zero to be called, or give some hint it's null
	SDL_Rect { 64, 32, 32, 32 },
	SDL_Rect { 0, 0, 32, 32 },
	SDL_Rect { 64, 0, 32, 32 },
	SDL_Rect { 0, 32, 32, 32 },
	SDL_Rect { 0, 64, 32, 32 },
	SDL_Rect { 128, 0, 72, 112 },
	SDL_Rect { 128, 112, 120, 100 },
	SDL_Rect { 128, 216, 44, 36 },
	SDL_Rect { 108, 217, 36, 60 },
	SDL_Rect { 220, 0, 32, 32 },
	SDL_Rect { 220, 32, 32, 32 },
	SDL_Rect { 220, 64, 32, 32 },
	// civilian idling
	SDL_Rect { 416, 36, 34, 34 },
	SDL_Rect { 416, 72, 34, 34 },
	SDL_Rect { 416, 108, 34, 34 },
	SDL_Rect { 416, 146, 34, 34 },
	// civilian walking
	SDL_Rect { 416, 36, 103, 34 },
	SDL_Rect { 416, 72, 102, 34 },
	SDL_Rect { 416, 108, 100, 36 },
	SDL_Rect { 416, 146, 99, 34 },
	// civilian running
	SDL_Rect { 416, 36, 103, 34 },
	SDL_Rect { 416, 72, 102, 34 },
	SDL_Rect { 416, 108, 100, 36 },
	SDL_Rect { 416, 146, 99, 34 },
	// player idling 
	SDL_Rect { 416, 408, 52, 59 },
	SDL_Rect { 416, 330, 52, 59 },
	SDL_Rect { 416, 258, 52, 59 },
	SDL_Rect { 416, 183, 52, 59 },
	// player walking
	SDL_Rect { 416, 408, 197, 59 },
	SDL_Rect { 416, 330, 197, 59 },
	SDL_Rect { 416, 258, 197, 59 },
	SDL_Rect { 416, 183, 197, 59 },
	// player running
	SDL_Rect { 416, 408, 197, 59 },
	SDL_Rect { 416, 330, 197, 59 },
	SDL_Rect { 416, 258, 197, 59 },
	SDL_Rect { 416, 183, 197, 59 },
	// objects
	SDL_Rect { 284, 0, 26, 19 },
	SDL_Rect { 284, 21, 19, 15 },
	SDL_Rect { 284, 38, 25, 14 }, 
	SDL_Rect { 284, 53, 16, 21 },
	SDL_Rect { 284, 76, 32, 32 },
	SDL_Rect { 284, 108, 32, 32 },
	SDL_Rect { 284, 141, 32, 32 },
	SDL_Rect { 284, 143, 20, 10 },
	SDL_Rect { 284, 156, 11, 14 },
	SDL_Rect { 284, 156, 11, 14 },
	SDL_Rect { 284, 156, 11, 14 }
};

class TextureAtlas 
{
	SDL_Texture* atlas;
	SDL_Rect src, dest;
	
	public:
		// init with full atlas image
		TextureAtlas(SDL_Texture* atlas);
		// draws image given by textureId to given SDL_Surface at x,y 
		void draw(SDL_Renderer* renderer, int textureId, float x, float y);
		// draws subimage defined by src from specified image to coordinates x,y on renderer
		void drawSubimg(SDL_Renderer* renderer, int textureId, SDL_Rect src, float x, float y);
		// returns width (px) of specified Texture image
		int getWidth(int textureId);
		// returns height (px) of specified Texture image
		int getHeight(int textureId);
};
#endif