#ifndef CIVILIAN_SPRITE_CONTROLLER_H
#define CIVILIAN_SPRITE_CONTROLLER_H

#include "sprite_controller.h"
#include "civilian_sprite.h"

// Provides the controller for a CivilianSprite

class CivilianSpriteController : public SpriteController
{
	private:
		// action the sprite is currently following
		Action* currAction = NULL;
	
	public:
		CivilianSpriteController(CivilianSprite* civilianSprite);
		
		// updates state of sprite by given number of milliseconds
		void update(int ms);

		// responds to sprite being attacked
		void handleAttacked(Attack* attack); 
		// handles sprite hearing a sound 
		void handleSoundHeard(Sound* sound);
		// handles sprite seeing another sprite 
		void handleSpriteSeen(Sprite* sprite);
};
#endif