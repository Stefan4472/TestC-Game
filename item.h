#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>
#include "constants.h"
#include "texture_atlas.h"
#include "attack.h"
class Action;

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
	ITEM_BULLET
};

// TextureAtlas image ids, mapped by ItemType id
const int ITEM_IMAGES[8] =
{
	BREAD_LOAF,
	CHICKEN_LEG,
	BEER_MUG,
	POTION_GREEN,
	SCROLL_1,
	SWORD_1,
	OBJECT_PISTOL_1,
	PISTOL_BULLET
};

// In-game item names, mapped by ItemType id
const std::string ITEM_NAMES[8] = 
{
	"Bread Loaf",
	"Chicken Leg",
	"Beer Mug",
	"Green Potion",
	"Scroll",
	"Sword",
	"Pistol",
	"Pistol Bullet"
};

// Item descriptions, mapped by ItemType id
const std::string ITEM_DESCRIPTIONS[8] = 
{
	"A Loaf of Bread",
	"Chicken Leg. Very tasty",
	"A big mug o' beer",
	"Not sure what it does, but it's green",
	"Some weird crinkled piece of paper with writing on it",
	"Sharp Steel",
	"Fancy-looking pistol. Bang bang!",
	"Small, metallic cylinder. For pistol use only!"
};	

// Stack amounts, mapped by ItemType id
const int ITEM_STACKSIZES[8] =
{
	16,
	16,
	4,
	4,
	1,
	1,
	1,
	24
};

// An item is the base class for anything that can be picked up or kept in inventory.
// An item must implement a use() method, and can override getAction(), getBuff(), and
// getAttack() if using the Item creates those effects. TODO: REQUIREMENTS (ITEMTYPE IDS)
// Once used, at Item will be deleted iff the item's destroy = True.
// An Item can be displayed in the Game as a Drop, in the Inventory as a widget, and on 
// the screen as part of a HUD that gives information about itself. 
class Item
{
	private:
		void init(TextureAtlas* textureAtlas, int itemType); // TODO: ON EQUIPPED, ON DE-EQUIPPED METHODS
		
	public:
		// ItemType id
		int itemType;
		// id for sprite in texture_atlas.h
		int textureId;
		// name and description of the item
		std::string name;
		std::string description;
		// number of this item that can go in one inventory slot
		int stackSize = 0;
		// pointer to TextureAtlas used for drawing
		TextureAtlas* textureAtlas = NULL;
		// id of item type that can be used to reload this item (default to 0 i.e. none)
		int ammunitionId = 0;
	
		// defines position of Item on the map
		SDL_Rect position = {0, 0, 0, 0};
		// whether item should be destroyed (removed from inventory and deleted)
		bool destroy = false;
		
		// sets textureAtlas and image, name, and description based on ItemType
		Item(TextureAtlas* textureAtlas, int itemType);
		// same as above but sets position to the top-left coordinates, with width/height 
		// the same as the textureId's dimensions
		Item(TextureAtlas* textureAtlas, int itemType, float x, float y);
		
		// returns name of the item
		const char* getName();
		// sets top-left of item position
		void setPosition(float x, float y);
		// called when the Item is used. Isn't required to do anything. May trigger change of state.
		// takes sprite that is using the item, sprite's hand position, and facing direction on Map
		virtual void use(Sprite* actor, SDL_Point handPos, int useDir) = 0;
		// attempts to reload with the given Item, which can be consumed. Returns whether the given
		// item was used to reload.
		virtual bool reload(Item* item);
		// updates state of item by given number of milliseconds. Meant for when item is in sprite's hand.
		// default does nothing.
		virtual void update(int ms);
		// returns Action created when this sprite is used. Default NULL
		virtual Action* getAction();
		// returns Buff created when this sprite is used. Default NULL
		virtual Action* getBuff();
		// returns Attack created when this sprite is used. Default NULL
		virtual Attack* getAttack();
		// draws item to given coordinate on renderer
		virtual void drawTo(SDL_Renderer* renderer, int x, int y);
		// draws item to map using its own coordinates, and the given offsets
		virtual void drawToMap(SDL_Renderer* renderer, int offsetX, int offsetY);
		virtual void drawToInventory(SDL_Renderer* renderer, SDL_Rect dest);
		// TODO: virtual void drawToHUD()
};

#endif