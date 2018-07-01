#ifndef ANIMATION_PLAYER_H
#define ANIMATION_PLAYER_H

#include <SDL2/SDL.h>
#include <assert.h>
#include "animation_sequence.h"

// Plays an AnimationSequence. Set the AnimationSequence through the set() method, and call
// update() and draw() as per usual. Attempt to set/change direction via setDir().

class AnimationPlayer
{
		// pointer to texture atlas
		TextureAtlas* textureAtlas = NULL;
		// source and destination rects for drawing
		SDL_Rect src = {0, 0, 0, 0}, dest = {0, 0, 0, 0};
		// sequence being played
		AnimationSequence* animSequence = NULL;
		// current Spritesheet being played
		Spritesheet* currAnim = NULL;
		// direction currently set to. defaults to DOWN
		int dir = DIRECTION::DIRECTION_NONE;
		// frame index currently on
		int frameCounter;
		// number of milliseconds this frame should keep playing for
		int msLeftThisFrame;

	public:
		AnimationPlayer(TextureAtlas* textureAtlas);
		// sets sequence to play
		void setAnimSequence(AnimationSequence* sequence);
		// sets direction
		void setDir(int dir);
		// increments duration by given number of milliseconds
		void update(int ms);
		// draws current AnimationSequence to given renderer (via currAnim)
		void drawTo(SDL_Renderer* renderer, float x, float y);
};

#endif
