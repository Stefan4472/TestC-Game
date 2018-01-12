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
	ITEM_PISTOL
};

// TextureAtlas image ids, mapped by ItemType id
const int ITEM_IMAGES[7] =
{
	BREAD_LOAF,
	CHICKEN_LEG,
	BEER_MUG,
	POTION_GREEN,
	SCROLL_1,
	SWORD_1,
	OBJECT_PISTOL_1
};

// In-game item names, mapped by ItemType id
const std::string ITEM_NAMES[7] = 
{
	"Bread Loaf",
	"Chicken Leg",
	"Beer Mug",
	"Green Potion",
	"Scroll",
	"Sword",
	"Pistol"
};

// Item descriptions, mapped by ItemType id
const std::string ITEM_DESCRIPTIONS[7] = 
{
	"A Loaf of Bread",
	"Chicken Leg. Very tasty",
	"A big mug o' beer",
	"Not sure what it does, but it's green",
	"Some weird crinkled piece of paper with writing on it",
	"Sharp Steel",
	"Fancy-looking pistol. Bang bang!"
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
		void init(TextureAtlas* textureAtlas, int itemType);
		
	protected:
		// ItemType id
		int itemType;
		// id for sprite in texture_atlas.h
		int textureId;
		// name and descripion of the item
		std::string name;
		std::string description;
		// pointer to TextureAtlas used for drawing
		TextureAtlas* textureAtlas = NULL;
	
	public: 
		// defines position of Item on the map
		SDL_Rect hitbox = {0, 0, 0, 0};
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
		// takes sprite's hand position and facing direction on Map
		virtual void use(SDL_Point handPos, int useDir) = 0;
		// returns Action created when this sprite is used. Default NULL
		virtual Action* getAction();
		// returns Buff created when this sprite is used. Default NULL
		virtual Action* getBuff();
		// returns Attack created when this sprite is used. Default NULL
		virtual Attack* getAttack();
		// handles given sprite interacting with the object on the ground -- removed due to forward declaration errors
		//virtual void handleInteract(Sprite* sprite);
		virtual void drawToMap(SDL_Renderer* renderer, int offsetX, int offsetY);
		virtual void drawToInventory(SDL_Renderer* renderer, SDL_Rect dest);
		// TODO: virtual void drawToHUD()
};

#endif