#ifndef ANIMATION_SEQUENCE_H
#define ANIMATION_SEQUENCE_H

#include <vector>
#include "spritesheet.h" 

// Defines how to draw an animation. Can include multiple spritesheets at different offsets.

class AnimationSequence // TODO: ADD COMPLEXITY AS NECESSASRY
{
	// spritesheets to be played
	std::vector<Spritesheet*> spritesheets;
	// offset from given (x, y) to draw animation
	SDL_Point offset = SDL_Point { 0, 0 };
	
	public:
		AnimationSequence();
		// update state by given number of milliseconds
		void update(int ms);
		// adds spritesheet to the sequence
		void addAnim(Spritesheet* toAdd);
};

#endif