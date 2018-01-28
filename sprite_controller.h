#ifndef SPRITE_CONTROLLER_H
#define SPRITE_CONTROLLER_H

#include "sprite.h"
#include "action.h"

// The SpriteController provides the AI controlling a sprite. It is essentially a Finite State Machine
// that manages the action a Sprite is currently following, and handles responses to certain events/
// triggers. 

// The Controller is abstracted, so different Sprite Classes may define their own handlers and controlling
// actions.

class SpriteController 
{
	protected:
		// list of buffs currently affecting player
		std::vector<Action*> buffs;
	
	public:
		SpriteController(Sprite* sprite);
		// the sprite being controlled
		Sprite* sprite = NULL;
		
		// updates state of sprite by given number of milliseconds
		virtual void update(int ms) = 0;
		
		// responds to sprite being attacked
		virtual void handleAttacked(Attack* attack) = 0; 
		// handles sprite hearing a sound 
		virtual void handleSoundHeard(Sound* sound) = 0;
		// handles sprite seeing another sprite 
		virtual void handleSpriteSeen(Sprite* sprite) = 0;
	
};
#endif