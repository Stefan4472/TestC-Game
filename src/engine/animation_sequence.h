#ifndef ANIMATION_SEQUENCE_H
#define ANIMATION_SEQUENCE_H

#include <SDL2/SDL.h>  // TODO: 2D_POINT UTILITY CLASS/struct
#include <vector>
#include "character_animation.h"

using namespace std;

/*
defines how to draw one or multiple character_animations in parallel
*/
// Defines how to draw an animation, which may be made up of multiple CharacterAnimations.
// TODO: EXPLAIN. TODO: Can include multiple spritesheets at different offsets.
// Contains one spritesheet for each direction. May be null if that direction is not permitted.
// Does not contain stateful information--that role is delegated to AnimationPlayer

class AnimationSequence // TODO: ADD COMPLEXITY AS NECESSASRY
{
	private:
		int numAnims = 0;
		
	public:
		AnimationSequence();

		// spritesheets to be played in parallel
		vector<CharacterAnimation*> anims;  // TODO: WHERE TO STORE OFFSETS?
		vector <SDL_Point> offsets; // TODO: NOT GOOD--DIFFERENT DIRECTIONS COULD HAVE DIFFERENT OFFSETS

		// TODO: MAKE IT POSSIBLE TO REMOVE? WE'D NEED TO RETURN AN INT INDEX FOR REMOVAL
		void addAnimation(CharacterAnimation* anim, int drawOffsetX=0, int drawOffsetY=0);

		int getNumAnimations();

};

#endif
