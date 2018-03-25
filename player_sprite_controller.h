#ifndef PLAYER_SPRITE_CONTROLLER_H
#define PLAYER_SPRITE_CONTROLLER_H

#include "texture_atlas.h"
#include "sprite_controller.h"
#include "path_finder_interface.h"
#include "knockback_action.h"
#include "colors.h"
#include "player_hud.h"

// Controller for the PlayerSprite. Takes Keyboard Input to determine what to do.

// Sometimes, the player will be forced to follow a certain action, e.g. Knockback
// or Stun. In this case, keyboard input will be ignored.

class PlayerSpriteController : public SpriteController
{
	private:
		// set aiming position for sprite based on on-screen coordinates of mouse
		void setAim(int mouseX, int mouseY);
		
	public:
		PlayerSpriteController(Sprite* playerSprite, PathFinder* pathFinder); 
		
		// pointer to PathFinder interface. Used to convert mouse coordinates to in-world coordinates
		PathFinder* pathFinder = NULL;
		// heads-up-display showing user informatin on current status
		PlayerHUD* hud = NULL;
		
		// whether player pressed key to interact
		bool interactPressed = false;
		// whether interact request was handled by Map
		bool interactHandled = false;
		
		// handles given event, and returns if it was consumed
		bool handleKeyEvent(SDL_Event e);
		// called when in-hand item changes: update HUD
		void onInHandItemChanged(Item* newItem);
		// called when hp changes: update HUD
		void onSpriteHealthChanged(int amount, int currHp);
		
		// updates state of sprite by given number of milliseconds
		void update(int ms);

		// responds to sprite being attacked--implements knockback
		void handleAttacked(Attack* attack); 
};

#endif