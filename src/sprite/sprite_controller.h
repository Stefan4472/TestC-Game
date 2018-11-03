#ifndef SPRITE_CONTROLLER_H
#define SPRITE_CONTROLLER_H

#include <SDL2/SDL.h>
#include <stack>
#include "animation_engine.h"
#include "animation_player.h"
#include "sprite.h"
#include "direction.h"
#include "move_state.h"
#include "sprite_healthbar.h"
#include "sprite_action.h"
#include "inventory.h"
#include "attack.h"
#include "sound.h"

using namespace std;

// The SpriteController provides the AI controlling a sprite. It is essentially a Finite State Machine
// that manages the action a Sprite is currently following, and handles responses to certain events/
// triggers.

// The Controller is abstracted, so different Sprite Classes may define their own handlers and controlling
// actions.

class SpriteController : public InventoryListener, public SpriteListener
{
	public:
		SpriteController(Sprite* sprite, Inventory* inventory, TextureAtlas* textureAtlas,
			AnimationEngine* animEngine);

		// the sprite being controlled
		Sprite* sprite = NULL;
		// sprite's inventory
		Inventory* inventory = NULL;
		// item sprite has in hand. Used for drawing
		Item* inHand = NULL;

		AnimationEngine* animEngine = NULL;
		AnimationPlayer* animPlayer = NULL;

		// healthbar, which may be drawn over the sprite
		SpriteHealthBar* healthbar = NULL;
		// number of ms to show healthbar (0 = do not show)
		int showHealthbarMs = 0;

		// milliseconds since sprite last made a footstep sound
		int msSinceFootstep = 0;

		// stack of Actions sprite will complete
		stack<SpriteAction*> actionStack;
		// list of ItemStacks sprite wants to drop. Meant to be picked up by the Map/Gamedriver
		vector<ItemStack*> drops;
		// list of Attacks sprite wants to carry out. Meant to be picked up by the Map/Gamedriver
		// a sprite may have multiple attacks progressing, e.g. if several bullets have been fired
		vector<Attack*> attacks;
		// list of Sounds the sprite has requested. Meant to be picked up by the Map/Gamedriver
		vector<Sound> sounds;
		// list of buffs currently affecting the sprite
		vector<SpriteBuff*> buffs;
		// list of sprites that are friends TODO: HASHMAP
		vector<Sprite*> friends;
		// list of sprites that are enemies. The sprite may act hostile when it sees them TODO: HASHMAP
		vector<Sprite*> enemies;

		// updates state of sprite by given number of milliseconds
		// by default updates all attacks as well as inhand item--DOES NOT CHANGE OR APPLY ACTIONSTACK!!
		virtual void update(int ms);

		// inventory callback when in-hand item has changed
		virtual void onInHandItemChanged(Item* newItem);

		// SpriteListener callback when sprite's movement state changes
		virtual void onMovementChanged(Direction dir, MoveState moveState);
		// SpriteListener callback when hp changes
		virtual void onSpriteHealthChanged(int amount, int newHp);

		// responds to sprite running into an object or invalid position on the Map TODO: SEPARATE INTO COLLISION AND INVALID SPACE
		virtual void handleMapCollision();
		// responds to sprite running into another sprite
		virtual void handleSpriteCollision(Sprite* other);
		// responds to sprite being attacked
		virtual void handleAttacked(Attack* attack);
		// handles sprite hearing a sound
		virtual void handleSoundHeard(Sound* sound);
		// handles sprite seeing another sprite
		virtual void handleSpriteSeen(Sprite* sprite);
		// handles sprite's health hitting or dropping below zero
		virtual void handleSpriteDead();

		// draws sprite to the screen
		virtual void drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas, int offsetX, int offsetY);

};
#endif
