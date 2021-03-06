#ifndef CIVILIAN_SPRITE_CONTROLLER_H
#define CIVILIAN_SPRITE_CONTROLLER_H

#include "sprite_controller.h"
#include "wander_action.h"
#include "path_finder_interface.h"
#include "follow_sprite_action.h"
#include "knockback_action.h"
#include "move_in_dir_action.h"
#include "idle_action.h"

// Provides the controller for a CivilianSprite.

class CivilianSpriteController : public SpriteController
{
	private:
		// hook to map via PathFinder interface
		PathFinder* pathFinder = NULL;
		
		Sprite* attackOrder = NULL;
		Sprite* fleeOrder = NULL;
		bool takeEffectOrder = false;
		SpriteAction* currAction = NULL;
	
	public:
		CivilianSpriteController(Sprite* civilianSprite, PathFinder* pathFinder);
		
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