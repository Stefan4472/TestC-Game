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

// Items in the game. These are used as keys to retrieve name and description from the const arrays
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

// TextureAtlas image ids, mapped by ItemType id TODO: MOVE THIS STUFF OUT TO A .CPP FILE
const TextureId ITEM_TEXTURES[13] =
{
	TextureId::TEXTURE_NONE,
	TextureId::BREAD_LOAF,
	TextureId::CHICKEN_LEG,
	TextureId::BEER_MUG,
	TextureId::POTION_GREEN,
	TextureId::SCROLL_1,
	TextureId::SWORD_1,
	TextureId::OBJECT_PISTOL_1,
	//PISTOL_BULLET,
	TextureId::TEXTURE_PISTOL_AMMO,
	TextureId::TEXTURE_SHOTGUN_AMMO,
	TextureId::TEXTURE_RIFLE_AMMO,
	TextureId::TEXTURE_SHOTGUN,
	TextureId::TEXTURE_TOMMYGUN
};

// In-game item names, mapped by ItemType id
const std::string ITEM_NAMES[13] =
{
	"The Null Item",
	"Bread Loaf",
	"Chicken Leg",
	"Beer Mug",
	"Green Potion",
	"Scroll",
	"Sword",
	"Pistol",
	"Pistol Bullet",
	"Shotgun Shell",
	"Rifle Bullet",
	"Double-Barelled Shotgun",
	"Tommy Gun"
};

// Item descriptions, mapped by ItemType id
const std::string ITEM_DESCRIPTIONS[13] =
{
	"Nothing. This is probably a bug",
	"A Loaf of Bread",
	"Chicken Leg. Very tasty",
	"A big mug o' beer",
	"Not sure what it does, but it's green",
	"Some weird crinkled piece of paper with writing on it",
	"Sharp Steel",
	"Fancy-looking pistol. Bang bang!",
	"Small, metallic cylinder. For pistol use only!",
	"Shell for a shotgun",
	"Rifle bullet",
	"Nasty Double-Barelled Shotgun. Might be from the Civil War",
	"Not your grandma's Tommy Gun"
};

// Stack amounts, mapped by ItemType id
const int ITEM_STACKSIZES[13] =
{
	1,
	16,
	16,
	4,
	4,
	1,
	1,
	1,
	48,
	24,
	32,
	1,
	1
};

// ItemIds of ammunition given Item takes
const ItemType ITEM_AMMUNITIONS[13] =
{
	ItemType::NONE,
	ItemType::NONE,
	ItemType::NONE,
	ItemType::NONE,
	ItemType::NONE,
	ItemType::NONE,
	ItemType::NONE,
	ItemType::PISTOL_AMMO,
	ItemType::NONE,
	ItemType::NONE,
	ItemType::NONE,
	ItemType::SHOTGUN_AMMO,
	ItemType::RIFLE_AMMO
};

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
		std::string name;
		std::string description;
		int stackSize = 0;
		TextureId textureId = TextureId::TEXTURE_NONE;

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
