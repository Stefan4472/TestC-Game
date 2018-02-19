#ifndef PLAYER_SPRITE_CONTROLLER_H
#define PLAYER_SPRITE_CONTROLLER_H

#include "sprite_controller.h"
#include "player_sprite.h"
#include "knockback_action.h"
#include "colors.h"
#include "player_hud.h"

// Controller for the PlayerSprite. Takes Keyboard Input to determine what to do.

// Sometimes, the player will be forced to follow a certain action, e.g. Knockback
// or Stun. In this case, keyboard input will be ignored.

class PlayerSpriteController : public SpriteController
{
	public:
		PlayerSpriteController(PlayerSprite* playerSprite);
		
		// pointer to the PlayerSprite
		// must be maintained separately from Sprite* pointer included in SpriteController base class
		PlayerSprite* player = NULL;
		
		PlayerHUD* hud = NULL;
		
		// whether player pressed key to interact
		bool interactPressed = false;
		// whether interact request was handled by Map
		bool interactHandled = false;
		
		// handles given event, and returns if it was consumed
		bool handleKeyEvent(SDL_Event e);
		
		// updates state of sprite by given number of milliseconds
		void update(int ms);

		// responds to sprite being attacked--implements knockback
		void handleAttacked(Attack* attack); 
};

#endif