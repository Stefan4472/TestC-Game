#ifndef ANIMATION_PLAYER_H
#define ANIMATION_PLAYER_H

#include <SDL2/SDL.h>
#include <iostream>
#include <assert.h>
#include <stdexcept>
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
TODO: REFACTORING AND IMPROVEMENTS ONCE USAGE IS BETTER UNDERSTOOD
*/

class AnimationPlayer
{
		// sequence being played
		AnimationSequence* currSequence = NULL;
		// current direction of spritesheets being played
		Direction currDir = Direction::NONE;

		vector<int> frameCounters;
		vector<int> msLeftThisFrame;
		vector<SDL_Rect> srcRects;

	public:
		AnimationPlayer();
		AnimationPlayer(AnimationSequence* initSequence, Direction initDirection);

		// stops the current sequence and begins the given one from the front
		void setAnim(AnimationSequence* sequence);
		// sets direction
		void setDir(Direction newDir);
		// increments duration by given number of milliseconds
		void update(int ms);
		// draws current AnimationSequence to given renderer (via currAnim) TODO: BOOL USE_OFFSET
		void drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas, float x, float y);
};

#endif
