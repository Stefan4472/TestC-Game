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
	TOMMYGUN,
	NUM_ITEMS
};

// TextureAtlas image ids, mapped by ItemType id. Defined in item.cpp
extern const TextureId ITEM_TEXTURES[int(ItemType::NUM_ITEMS)];
// In-game item names, mapped by ItemType id. Defined in item.cpp
extern const std::string ITEM_NAMES[int(ItemType::NUM_ITEMS)];
// Item descriptions, mapped by ItemType id. Defined in item.cpp
extern const std::string ITEM_DESCRIPTIONS[int(ItemType::NUM_ITEMS)];
// Maximum allowed ItemStack sizes, mapped by ItemType id. Defined in item.cpp
extern const int ITEM_STACKSIZES[int(ItemType::NUM_ITEMS)];
// ItemIds of ammunition the given Item takes (NONE = cannot be reloaded)
extern const ItemType ITEM_AMMUNITIONS[int(ItemType::NUM_ITEMS)];

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

		// id of the item
		ItemType itemId;
		std::string name;  // TODO: HOW OFTEN ARE THESE NEEDED? CAN WE REPLACE THEM WITH GET() METHODS
		std::string description;
		int stackSize = 0;
		TextureId textureId = TextureId::TEXTURE_NONE;
		ItemType ammunitionType = ItemType::NONE;

		// whether item should be destroyed (removed from inventory and deleted)
		bool destroy = false;

		// creates item with given ID
		Item(int itemId);

		// attempts to load this item with the given Item, which may be consumed
		// (setting the item's delete = true). Returns whether the given was
		// successfully loaded into the current item.
		virtual bool load(Item* item);  // TODO: TAKE ITEMSTACK PARAMETER

		// called when the Item is used. By default, doesn't do anything. Meant to
		// be overridden by Items that create some action or consequence when used.
		// May trigger change of state.
		// Actor is the sprite that's using the item
		virtual void use(const Sprite* actor);

		// updates state of item by given number of milliseconds. Meant for when
		// item is in the sprite's hand. By default does nothing.
		virtual void update(int ms);

		// returns SpriteAction created when this sprite is used. Default NULL
		virtual SpriteAction* getAction();
		// returns Buff created when this sprite is used. Default NULL
		virtual SpriteBuff* getBuff();
		// returns Attack created when this sprite is used. Default NULL
		virtual Attack* getAttack();
		// consumes the sounds created by the item (if any) and adds them to the
		// given list
		virtual void getAndClearSounds(vector<Sound*> sounds) = 0;

		// returns stack size of given item id
		static int getStackSize(int itemId);
		// returns texture id of given item id
		static TextureId getTextureId(int itemId);
};


#endif
