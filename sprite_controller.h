#ifndef SPRITE_CONTROLLER_H
#define SPRITE_CONTROLLER_H

#include <stack>
#include "sprite.h"
#include "action.h"
#include "inventory.h"
#include "attack.h"
#include "sound.h"

// The SpriteController provides the AI controlling a sprite. It is essentially a Finite State Machine
// that manages the action a Sprite is currently following, and handles responses to certain events/
// triggers. 

// The Controller is abstracted, so different Sprite Classes may define their own handlers and controlling
// actions.

class SpriteController : public InventoryListener, public SpriteListener
{
	public:
		SpriteController(Sprite* sprite);
		
		// the sprite being controlled
		Sprite* sprite = NULL;
		// sprite's inventory
		Inventory* inventory = NULL;  // TODO: SHOULD THIS BE IN THE SPRITE CLASS?? SPRITE NEEDS TO KNOW WHICH ITEM IT HAS IN-HAND
		// stack of Actions sprite will complete
		std::stack<Action*> actionStack;
		// list of Items sprite wants to drop. Meant to be picked up by the Map/Gamedriver
		std::vector<Item*> drops;
		// list of Attacks sprite wants to carry out. Meant to be picked up by the Map/Gamedriver
		// a sprite may have multiple attacks progressing, e.g. if several bullets have been fired
		std::vector<Attack*> attacks;
		// list of SoundIds the sprite has requested. Meant to be picked up by the Map/Gamedriver
		std::vector<int> sounds;
		// list of buffs currently affecting player
		std::vector<Action*> buffs;
		// list of sprites that are friends TODO: HASHMAP
		std::vector<Sprite*> friends;
		// list of sprites that are enemies. The sprite may act hostile when it sees them TODO: HASHMAP
		std::vector<Sprite*> enemies;
		
		// updates state of sprite by given number of milliseconds
		// by default updates all attacks as well as inhand item--DOES NOT CHANGE OR APPLY ACTIONSTACK!!
		virtual void update(int ms);
		
		// inventory callback when in-hand item has changed. Sends to sprite by default
		void onInHandItemChanged(Item* newItem);
		// sprite callback when hp changes
		void onSpriteHealthChanged(int amount, int currHp);
		
		// responds to sprite running into an object or invalid position on the Map
		virtual void handleMapCollision();
		// responds to sprite running into another sprite
		virtual void handleSpriteCollision(Sprite* other);
		// responds to sprite being attacked
		virtual void handleAttacked(Attack* attack); 
		// handles sprite hearing a sound 
		virtual void handleSoundHeard(Sound* sound);
		// handles sprite seeing another sprite 
		virtual void handleSpriteSeen(Sprite* sprite);
	
};
#endif