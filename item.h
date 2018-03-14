#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>
#include "constants.h"
#include "texture_atlas.h"
#include "attack.h"
class SpriteAction;

// Items in the game. These are used as keys to retrieve name and description from the const arrays
enum ItemType
{
	ITEM_BREAD_LOAF,
	ITEM_CHICKEN_LEG,
	ITEM_BEER_MUG,
	ITEM_GREEN_POTION,
	ITEM_SCROLL,
	ITEM_SWORD,
	ITEM_PISTOL,
	ITEM_PISTOL_AMMO,
	ITEM_SHOTGUN_AMMO,
	ITEM_RIFLE_AMMO
};

// TextureAtlas image ids, mapped by ItemType id
const int ITEM_TEXTURES[10] =
{
	BREAD_LOAF,
	CHICKEN_LEG,
	BEER_MUG,
	POTION_GREEN,
	SCROLL_1,
	SWORD_1,
	OBJECT_PISTOL_1,
	//PISTOL_BULLET,
	TEXTURE_PISTOL_AMMO,
	TEXTURE_SHOTGUN_AMMO,
	TEXTURE_RIFLE_AMMO
};

// In-game item names, mapped by ItemType id
const std::string ITEM_NAMES[10] = 
{
	"Bread Loaf",
	"Chicken Leg",
	"Beer Mug",
	"Green Potion",
	"Scroll",
	"Sword",
	"Pistol",
	"Pistol Bullet",
	"Shotgun Shell",
	"Rifle Bullet"
};

// Item descriptions, mapped by ItemType id
const std::string ITEM_DESCRIPTIONS[10] = 
{
	"A Loaf of Bread",
	"Chicken Leg. Very tasty",
	"A big mug o' beer",
	"Not sure what it does, but it's green",
	"Some weird crinkled piece of paper with writing on it",
	"Sharp Steel",
	"Fancy-looking pistol. Bang bang!",
	"Small, metallic cylinder. For pistol use only!",
	"Shell for a shotgun",
	"Rifle bullet."
};	

// Stack amounts, mapped by ItemType id
const int ITEM_STACKSIZES[10] =
{
	16,
	16,
	4,
	4,
	1,
	1,
	1,
	48,
	24,
	32
};

// ItemIds of ammunition given Item takes
const int ITEM_AMMUNITIONS[10] = 
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	ITEM_PISTOL_AMMO,
	NULL,
	NULL,
	NULL
};

// returns stack size of given item id
int getStackSize(int itemId);
// returns texture id of given item id
int getTextureId(int itemId);

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
		int itemId;
		std::string name;
		std::string description;
		int stackSize = NULL;
		int textureId = NULL;
		int ammunitionId = NULL; // TODO: IMPLEMENT ONLY IN GUN CLASS
		
		// whether item should be destroyed (removed from inventory and deleted)
		bool destroy = false;
		
		// creates item with given ID
		Item(int itemId);
		
		// called when the Item is used. By default, doesn't do anything. Meant to be overridden by Items that
		// create some action or consequence when used. May trigger change of state. actor is the sprite that 
		// is using the item
		virtual void use(const Sprite* actor);
		// attempts to load this item with the given Item, which can be consumed. Returns whether the given
		// item was used to reload.
		virtual bool load(Item* item);
		// updates state of item by given number of milliseconds. Meant for when item is in sprite's hand.
		// default does nothing.
		virtual void update(int ms);
		// returns SpriteAction created when this sprite is used. Default NULL
		virtual SpriteAction* getAction();
		// returns Buff created when this sprite is used. Default NULL
		virtual SpriteAction* getBuff();
		// returns Attack created when this sprite is used. Default NULL
		virtual Attack* getAttack();
};


#endif