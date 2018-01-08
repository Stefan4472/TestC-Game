#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>
#include "texture_atlas.h"

// types of Items in the game. These are used as keys to retrieve name and description from the const arrays
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

// in-game item names, mapped by ItemType id
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

// item descriptions, mapped by ItemType id
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

// an item is the base class for anything that can be picked up or kept in inventory.
// it has a sprite, a widget (for display in inventory), a hitbox, and a description
class Item
{
	protected:
		// ItemType id
		int itemType;
		// id for sprite in texture_atlas.h
		int textureId;
		std::string name;
		std::string description;
		// pointer to TextureAtlas used for drawing
		TextureAtlas* textureAtlas;
		
	public: // todo: make base class
	
		Item(TextureAtlas* textureAtlas, int itemType);
		// defines position of Item on the map
		SDL_Rect hitbox = {0, 0, 0, 0};
		// returns name of the item
		const char* getName();
		// sets top-left of item position
		void setPosition(float x, float y);
		// handles given sprite interacting with the object on the ground -- removed due to forward declaration errors
		//virtual void handleInteract(Sprite* sprite);
		virtual void drawToMap(SDL_Surface* screenSurface, int offsetX, int offsetY);
		virtual void drawToInventory(SDL_Surface* screenSurface, SDL_Rect dest);
		//virtual void use() = 0;
};

#endif