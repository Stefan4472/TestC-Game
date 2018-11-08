#ifndef PUNCH_ATTACK_H
#define PUNCH_ATTACK_H

#include <SDL2/SDL.h>
#include "texture_atlas.h"
#include "attack.h"
#include "direction.h"

// A punch is a (relatively weak) directional attack a sprite can execute without holding any item in its hand.

class Punch : public Attack
{
	// number of ms punch has existed
	int elapsedTime = 0;
	// maximum number of milliseconds this punch can exist before requesting destruction
	const int MAX_DURATION = 2000;
	// num pixels punch extends (width and height)
	const int PUNCH_WIDTH = 32, PUNCH_LENGTH = 32;
	public:
		Punch(SDL_Point handPos, Direction facingDir, Sprite* attacker);
		// returns position of attack on map given handposition and direction of sprite
		SDL_Rect getPos(SDL_Point handPos, Direction facingDir);
		void update(int ms);
		void handleSpriteCollision();
		void handleObjectCollision();
};

#endif
