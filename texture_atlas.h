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
	CIVILIAN_IDLE,
	CIVILIAN_MVRIGHT,
	CIVILIAN_MVLEFT,
	CIVILIAN_MVUP,
	CIVILIAN_MVDOWN,
	PLAYER_IDLE,
	PLAYER_MVDOWN,
	PLAYER_MVUP,
	PLAYER_MVLEFT,
	PLAYER_MVRIGHT,
	OBJECT_PISTOL_1,
	BREAD_LOAF,
	CHICKEN_LEG,
	BEER_MUG,
	SWORD_1,
	POTION_GREEN,
	SCROLL_1
};

const SDL_Rect textureRegions[30] = 
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
	SDL_Rect { 416, 0, 34, 34 },
	SDL_Rect { 416, 36, 103, 34 },
	SDL_Rect { 416, 72, 102, 34 },
	SDL_Rect { 416, 108, 100, 36 },
	SDL_Rect { 416, 146, 99, 34 },
	SDL_Rect { 416, 183, 52, 59 },
	SDL_Rect { 416, 183, 197, 59 },
	SDL_Rect { 416, 258, 197, 59 },
	SDL_Rect { 416, 330, 197, 59 },
	SDL_Rect { 416, 408, 197, 59 },
	SDL_Rect { 284, 0, 26, 19 },
	SDL_Rect { 284, 21, 19, 15 },
	SDL_Rect { 284, 38, 25, 14 }, 
	SDL_Rect { 284, 53, 16, 21 },
	SDL_Rect { 284, 76, 32, 32 },
	SDL_Rect { 284, 108, 32, 32 },
	SDL_Rect { 284, 141, 32, 32 }
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