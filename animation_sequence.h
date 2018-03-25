#ifndef ANIMATION_SEQUENCE_H
#define ANIMATION_SEQUENCE_H

#include <vector>
#include "constants.h"
#include "spritesheet.h" 

// Defines how to draw an animation. TODO: Can include multiple spritesheets at different offsets.
// Contains one spritesheet for each direction. May be null if that direction is not permitted.
// Does not contain stateful animation--that role is delegated to AnimationPlayer

class AnimationSequence // TODO: ADD COMPLEXITY AS NECESSASRY
{
	// spritesheets to be played
	//std::vector<Spritesheet*> spritesheets;
	
	// spritesheets, indexed by direction
	Spritesheet* anims[5] = { NULL, NULL, NULL, NULL, NULL };
	// offset from given (x, y) to draw animation
	SDL_Point offset = SDL_Point { 0, 0 };
	
	public:
		AnimationSequence(Spritesheet* right, Spritesheet* left, Spritesheet* up, Spritesheet* down);
		// adds spritesheet to the sequence
		//void addAnim(Spritesheet* right, Spritesheet* left, Spritesheet* up, Spritesheet* down);
};

#endif