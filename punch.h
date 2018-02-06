#ifndef PUNCH_ATTACK_H
#define PUNCH_ATTACK_H

#include <SDL2/SDL.h>
#include "texture_atlas.h"
#include "attack.h"

// A punch is a (relatively weak) directional attack a sprite can execute without holding any item in its hand.

class Punch : public Attack
{
	// number of ms punch has existed
	int elapsedTime = 0;
	// maximum number of milliseconds this punch can exist before requesting destruction
	const int MAX_DURATION = 2000;
	
	public:
		Punch(SDL_Rect position, int dir, Sprite* attacker);
		void update(int ms);
		void handleSpriteCollision();
		void handleObjectCollision();
};

#endif