#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "item.h"

// an inventory can store and keep track of Items
class Inventory
{
	// number of items that'll fit in the inventory
	int capacity = 10;
	// number of items currently stored in the inventory
	int numItems = 0;
	// array of pointers to items in storage
	Item* items[10] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }; // TODO: VARIABLE CAPACITY
		
	public:
		// attempts to add an item to inventory. Returns false if inventory is full
		bool addItem(Item* item);
};
#endif