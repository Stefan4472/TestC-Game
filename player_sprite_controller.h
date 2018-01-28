#ifndef PLAYER_SPRITE_CONTROLLER_H
#define PLAYER_SPRITE_CONTROLLER_H

#include "sprite_controller.h"
#include "player_sprite.h"

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