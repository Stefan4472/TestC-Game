#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <vector>
#include "texture_atlas.h"
#include "gui_window.h"
#include "gui_button.h"
#include "item.h"

// An inventory manages the Items a Sprite has and can use. It also manages the usage and effects of
// those items.
// Items are stored as pointers in a vector, so memory deallocation should not be done to live items.
// An inventory has an Item "in-hand", which can be used at any time. Items are referred to by
// their index in the vector.
// The Inventory stores the Actins, Buffs, and Attacks created by using the item in hand. These must
// be managed properly, as they will be overridden once the next item is used. They are accessed via
// the getAction(), getBuff(), and getAttack() methods.
// Example usage: Call inventory->useInHand(), then store inventory->getAction(), getBuff(), getAttack().
// Store those which are non-null.
class Inventory
{
	// number of items that'll fit in the inventory
	int capacity = 10;
	// vector of pointers to items in storage
	std::vector<Item*> items;
	// index of Item that's currently in hand
	int inHandIndex = -1;
	
	public:
		// creates enough space for the given number of items
		Inventory(int capacity);
		// attempts to add an item to inventory. Returns false if inventory is full
		bool addItem(Item* item);
		// draws inventory to given surface
		void drawTo(SDL_Surface* screenSurface, TextureAtlas* textureAtlas);
		// returns pointer to the Item that's currently in hand. Null if empty TODO: MAKE NON-NULL?
		Item* getInHand();
		// sets in hand item to the proceeding one in inventory, returns pointer to item now in hand.
		// doesn't do anything if vector has only 1 element
		Item* cycleInHandFwd();
		// sets in hand item to the preceeding one in inventory, returns pointer to item now in hand.
		// doesn't do anything if vector has only 1 element
		Item* cycleInHandBck();
		// removes and returns in-hand item, if it exists. Automatically cycles forward
		Item* removeInHand();
		// opens a Window with inventory displayed
		Window* getWindow();
};
#endif