#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <vector>
#include "texture_atlas.h"
#include "gui_window.h"
#include "gui_button.h"
#include "item.h"

// An inventory stores and keeps track of Items a Sprite has and can use.
// Items are stored as pointers in a vector, so memory deallocation should not be done to live items.
// An inventory has an Item "in-hand", which can be used at any time. Items are referred to by
// their index in the vector.
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
		// opens a Window with inventory displayed
		Window* getWindow();
};
#endif