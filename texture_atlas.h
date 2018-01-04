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
	BROWN_BRICK_TILE,
	DARK_BRICK_TILE,
	WHITE_BRICK_TILE,
	GRASS_TILE,
	WATER_TILE
};

/*SDL_Rect textureRegions[5] = 
{
	SDL_Rect { 0, 0, 32, 32 },
	SDL_Rect { 64, 0, 32, 32 },
	SDL_Rect { 0, 32, 32, 32 },
	SDL_Rect { 64, 0, 32, 32 },
	SDL_Rect { 0, 64, 32, 32 }
};*/

class TextureAtlas 
{
	public:
		// init with full atlas image
		TextureAtlas(SDL_Surface* atlas);
};
#endif