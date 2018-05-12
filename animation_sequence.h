#ifndef ANIMATION_SEQUENCE_H
#define ANIMATION_SEQUENCE_H

#include <vector>
#include <stdio.h>
#include "constants.h"
#include "spritesheet.h"

// Defines how to draw an animation. TODO: Can include multiple spritesheets at different offsets.
// Contains one spritesheet for each direction. May be null if that direction is not permitted.
// Does not contain stateful information--that role is delegated to AnimationPlayer

class AnimationSequence // TODO: ADD COMPLEXITY AS NECESSASRY
{
	// spritesheets to be played
	//std::vector<Spritesheet*> spritesheets;

	public:
		AnimationSequence(Spritesheet* right, Spritesheet* left, Spritesheet* up, Spritesheet* down);
		// spritesheets, indexed by direction
		Spritesheet* anims[5] = { NULL, NULL, NULL, NULL, NULL };
		// offset from given (x, y) to draw animation
		SDL_Point offset = SDL_Point { 0, 0 };
		// returns whether the sequence has an animation for the given direction
		bool hasDir(int dir);
		// prints information for debugging
		void printDebug();

		// adds spritesheet to the sequence
		//void addAnim(Spritesheet* right, Spritesheet* left, Spritesheet* up, Spritesheet* down);
};

#endif
