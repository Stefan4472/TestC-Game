#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include <SDL2/SDL.h>
#include <stdexcept>
#include "texture_ids.h"
#include "simple_animation.h"

using namespace std;

/*
Provides access to game graphics via a single "atlas" image. All used graphics
are placed in a single image. Individual images are retrieved by subimaging the
full atlas image with pre-determined, known SDL_Rects.

The TextureId enum, defined in texture_ids.h, provides image identifiers.
The textureRegions array defines the bounds of the corresponding textures in
the atlas.

The TextureAtlas also provides support for drawing SimpleAnimation types. TODO: EXPLAIN
*/

// note: this animations were not implemented.
// the Animations enum defines the animations that are known
// the AnimationFrames array defines the corresponding Textures that make up the animation

// call draw(textureId, ...) functions to draw the desired texture to the screen

// SDL_Rects defining the regions on the atlas that correspond to the TextureIds.
// defined in texture_atlas.cpp
extern const SDL_Rect textureRegions[51];

// 2-d array defining the TextureIds in the known animations.
// The first index corresponds to the AnimationId, and the second lists the
// frames of the animation, in order
extern const TextureId *animationFrames[2];
// defines the number of frames for each corresponding AnimationId
extern const int animationFrameCounts[2];
const int ANIMATION_FRAME_DURATION = 50; // TODO: FIND A BETTER WAY

class TextureAtlas
{
	SDL_Texture* atlasImg;
	SDL_Rect src, dest;

	public:
		// init with full atlas image
		TextureAtlas(SDL_Texture* atlasImg);

		// map coordinates of top-left of the screen. Subtracted from given draw
		// coordinates to convert map coordinates to physical (screen) coordinates.
		// Should be set by the Map/game engine
		float mapOffsetX = 0, mapOffsetY = 0;

		// returns width (px) of specified Texture image
		int getWidth(int textureId);
		// returns height (px) of specified Texture image
		int getHeight(int textureId);

		// draws image given by textureId to given SDL_Surface at x,y
		void drawImg(SDL_Renderer* renderer, int textureId, float x, float y,
			bool useMapOffset=true);
		// draws subimage defined by src from specified image to coordinates x,y on renderer
		void drawSubimg(SDL_Renderer* renderer, int textureId, SDL_Rect src, float x,
			float y, bool useMapOffset=true);
		// draws the frame from the given SimpleAnimation TODO: TAKE MAP OFFSET AS A PARAMETER? OR JUST USE ANIM COORDINATES?
		void drawAnim(SDL_Renderer* renderer, SimpleAnimation* anim,
			bool useMapOffset=true);
};
#endif
