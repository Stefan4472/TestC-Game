#ifndef SPRITE_CONTROLLER_H
#define SPRITE_CONTROLLER_H

#include "sprite.h"
#include "action.h"

// The SpriteController provides the AI controlling a sprite. It is essentially a Finite State Machine
// that manages the action a Sprite is currently following, and handles responses to certain events/
// triggers. The controller uses Actions, which utilize the Sprite interface.

class SpriteController
{
	// action the sprite is currently following
	Action* currAction = NULL;
	
	public:
		SpriteController(Sprite* sprite);
		// the sprite being controlled
		Sprite* sprite = NULL;
		// updates state of sprite by given number of milliseconds
		void update(int ms);
	
};
#endif