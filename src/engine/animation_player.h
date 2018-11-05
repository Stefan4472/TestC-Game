#ifndef ANIMATION_PLAYER_H
#define ANIMATION_PLAYER_H

#include <SDL2/SDL.h>
#include <assert.h>
#include <sdlexcept>
#include <vector>
#include "direction.h"
#include "texture_atlas.h"
#include "character_animation.h"
#include "animation_sequence.h"

using namespace std;

/*
Plays an AnimationSequence. Set the AnimationSequence through the set() method, and call
update() and draw() as per usual. Attempt to set/change direction via setDir().
TODO: SUPPORT ANIMATIONSEQUENCE INTERRUPT VIA A STACK
*/

class AnimationPlayer
{
		// source and destination rects for drawing
		SDL_Rect src = {0, 0, 0, 0}, dest = {0, 0, 0, 0};
		// sequence being played
		AnimationSequence* currSequence = NULL;
		// current direction of spritesheets being played
		Direction currDir = Direction::NONE;

		vector<int> frameCounters;
		vector<int> msLeftThisFrame;
		vector<Spritesheet*> currSpritesheets;

	public:
		AnimationPlayer();
		AnimationPlayer(AnimationSequence* initSequence, Direction initDirection);

		// sets sequence to play
		void setAnim(AnimationSequence* sequence);
		// sets direction
		void setDir(int dir);
		// increments duration by given number of milliseconds
		void update(int ms);
		// draws current AnimationSequence to given renderer (via currAnim) TODO: BOOL USE_OFFSET
		void drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas, float x, float y);
};

#endif
