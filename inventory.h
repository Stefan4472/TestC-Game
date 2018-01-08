#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <vector>
#include "texture_atlas.h"
#include "gui_window.h"
#include "gui_button.h"
#include "item.h"

// an inventory can store and keep track of Items
class Inventory
{
	// number of items that'll fit in the inventory
	int capacity = 10;
	// vector of pointers to items in storage
	std::vector<Item*> items;
	// item that is currently "in hand" and can be used immediately
	Item* inHand = NULL;
	
	public:
		// creates enough space for the given number of items
		Inventory(int capacity);
		// attempts to add an item to inventory. Returns false if inventory is full
		bool addItem(Item* item);
		// draws inventory to given surface
		void drawTo(SDL_Surface* screenSurface, TextureAtlas* textureAtlas);
		
		// opens a Window with inventory displayed
		Window* getWindow();
};
#endif