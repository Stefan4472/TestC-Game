#ifndef PLAYER_SPRITE_CONTROLLER_H
#define PLAYER_SPRITE_CONTROLLER_H

#include "texture_atlas.h"
#include "controller_adapter.h"
#include "sprite_controller.h"
#include "path_finder_interface.h"
#include "knockback_action.h"
#include "colors.h"
#include "player_hud.h"

// Controller for the PlayerSprite. Takes Keyboard Input to determine what to do.

// Sometimes, the player will be forced to follow a certain action, e.g. Knockback
// or Stun. In this case, keyboard input will be ignored.

class PlayerSpriteController : public SpriteController, public ControllerListener
{
	private:
		// set aiming position for sprite based on on-screen coordinates of mouse
		void setAim(int mouseX, int mouseY);

	public:
		PlayerSpriteController(Sprite* playerSprite, PathFinder* pathFinder, TextureAtlas* textureAtlas);

		// pointer to PathFinder interface. Used to convert mouse coordinates to in-world coordinates
		PathFinder* pathFinder = NULL;
		// heads-up-display showing user informatin on current status
		PlayerHUD* hud = NULL;

		// whether player pressed key to interact
		bool interactPressed = false;
		// whether interact request was handled by Map
		bool interactHandled = false;

		// handle a control started
		void onControlStart(GAME_CONTROLS gameControl);
		// handle a control finished
    void onControlEnd(GAME_CONTROLS gameControl);
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
