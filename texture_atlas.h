#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include <SDL2/SDL.h>

// provides access to graphics via a single tile "atlas"
// all used graphics are placed in a single image. Individual images are retrieved
// via subimaging the full atlas with a pre-determined, known SDL_Rect

// the Textures enum defines the graphics that may be used.
// the TextureRegions array defines the bounds of the corresponding textures in the atlas
// the Animations enum defines the animations that are known
// the AnimationFrames array defines the corresponding Textures that make up the animation

// call draw(textureId, ...) functions to draw the desired texture to the screen

enum Textures {
	TILE_BROWN_BRICK,
	TILE_DARK_BRICK,
	TILE_WHITE_BRICK,
	TILE_GRASS,
	TILE_WATER
};

const SDL_Rect textureRegions[5] = 
{
	SDL_Rect { 0, 0, 32, 32 },
	SDL_Rect { 64, 0, 32, 32 },
	SDL_Rect { 0, 32, 32, 32 },
	SDL_Rect { 64, 0, 32, 32 },
	SDL_Rect { 0, 64, 32, 32 }
};

class TextureAtlas 
{
	SDL_Surface* atlas;
	SDL_Rect src, dest;
	
	public:
		// init with full atlas image
		TextureAtlas(SDL_Surface* atlas);
		// draws image given by textureId to given SDL_Surface at x,y 
		void draw(SDL_Surface* screenSurface, int textureId, float x, float y);

};
#endif