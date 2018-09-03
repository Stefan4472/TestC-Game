#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include <SDL2/SDL.h>
#include "texture_ids.h"

/*
Provides access to game graphics via a single "atlas" image. All used graphics
are placed in a single image. Individual images are retrieved by subimaging the
full atlas image with pre-determined, known SDL_Rects.

The TextureId enum, defined in texture_ids.h, provides image identifiers.
The textureRegions array defines the bounds of the corresponding textures in
the atlas.
*/

// note: this animations were not implemented.
// the Animations enum defines the animations that are known
// the AnimationFrames array defines the corresponding Textures that make up the animation

// call draw(textureId, ...) functions to draw the desired texture to the screen

// SDL_Rects defining the regions on the atlas that correspond to the TextureIds.
// defined in texture_atlas.cpp
const SDL_Rect textureRegions[51];

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

		void drawAnim(SDL_Renderer* renderer, SimpleAnimation* anim, float mapOffsetX,
			float mapOffsetY);  // TODO: TAKE MAP OFFSET AS A PARAMETER? OR JUST USE ANIM COORDINATES?
};
#endif
