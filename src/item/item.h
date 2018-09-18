#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <string>
#include "constants.h"
#include "texture_atlas.h"
#include "attack.h"
#include "sprite_buff.h"
#include "sound.h"
class SpriteAction;

using namespace std;

// Defines the types of items in the game. Indexes used as keys to retrieve
// properties of the ItemType the const arrays
enum class ItemType
{
	NONE,
	BREAD_LOAF,
	CHICKEN_LEG,
	BEER_MUG,
	GREEN_POTION,
	SCROLL,
	SWORD,
	PISTOL,
	PISTOL_AMMO,
	SHOTGUN_AMMO,
	RIFLE_AMMO,
	SHOTGUN,
	TOMMYGUN
};

// number of ItemTypes, includeing ItemType::NONE
const int NUM_ITEM_TYPES = 13;

// TODO: UPDATE/REWRITE
// Item provides basic functionality for anything that can be picked up, used, and kept
// in inventory. Each Item must have certain fields, such as a texture, name, description,
// and stack size (number of items that can be stacked in one inventory slot). As these
// are generally standardized values, they are stored above in the various arrays, and
// indexed by itemId. So, an Item can be created solely using given an ID.

// An item must implement a use() method, and can override getAction(), getBuff(), and
// getAttack() if using the Item creates those effects.
//
// Once used, at Item will be deleted iff the item's destroy = True.
class Item
{
	// TODO: ON EQUIPPED, ON DE-EQUIPPED METHODS

	public:

		/* Static methods for retrieving properties of a specific ItemType */
		/* Looks up the ItemType in the relevant property array */
		static string getName(ItemType itemType);
		static string getDescription(ItemType itemType);
		static int getStackSize(ItemType itemType);
		static TextureId getTextureId(ItemType itemType);
		static ItemType getAmmunitionType(ItemType itemType);

		// type of the item: should be all that is needed to define the functionality
		// of the Item object
		ItemType itemType;

		// whether item should be destroyed (removed from inventory and deleted)
		// usually set by the Item itself once it has been used up
		bool destroy = false;

		// creates item with given Type
		Item(ItemType itemType);

		// TODO: MAKE THESE NECESSARY 
		// attempts to load this item with the given Item, which may be consumed
		// (setting the item's delete = true). Returns whether the given Item was
		// successfully loaded into the current item.
		virtual bool load(Item* item);

		// called when the Item is used. By default, doesn't do anything. Meant to
		// be overridden by Items that create some action or consequence when used.
		// May trigger change of state.
		// Actor is the sprite that's using the item
		virtual void use(const Sprite* actor);

		// updates state of item by given number of milliseconds. Does not need to
		// do anything
		virtual void update(int ms);

		// returns SpriteAction created when this sprite was last used. May be NULL
		virtual SpriteAction* getAction();
		// returns Buff created when this item was last used. May be NULL
		virtual SpriteBuff* getBuff();
		// returns Attack created when this item was last used. May be NULL
		virtual Attack* getAttack();

		// consumes the sounds created by the item (if any) and adds them to the
		// given list
		virtual void getAndClearSounds(vector<Sound*> sounds) = 0;

};


#endif
