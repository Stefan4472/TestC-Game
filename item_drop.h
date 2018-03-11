#ifndef ITEM_DROP_H
#define ITEM_DROP_H

#include <SDL2/SDL.h>
#include "item.h"
#include "item_stack.h"

// An ItemDrop is a wrapper to an ItemStack that is currently lying on the map and can
// be picked up. The ItemDrop has a coordinate on the map and a position it takes
// up, which allows it to be picked up.

class ItemDrop {
	
	private:
		// stack of items in the drop
		ItemStack* items = NULL;
		// sets top-left and right coordinates of drop
		void setPosition(float x, float y);
	
	public:
		// creates drop from single item, and map coordinates
		ItemDrop(Item* item, float x, float y);
		// creates drop from existing ItemStack, and map coordinates
		ItemDrop(ItemStack* itemStack, float x, float y);
		// creates drop containing a stack of the given number of specified item, and map coordinates
		ItemDrop(int itemId, int quantity, float x, float y);
		// returns ItemStack contained by the drop
		ItemStack* getItems();
	
		// defines position of Item on the map TODO: DON'T DEFAULT TO 32PX
		SDL_Rect position = {0, 0, 32, 32};
	
		// draws item drop to map (uses position)
		void drawToMap(SDL_Renderer* renderer, TextureAtlas* textureAtlas, int offsetX, int offsetY);
		
	// prepares for destruction: sets ItemStack to NULL. The ItemStack itself must
		// be  
		//~ItemStack();
};

#endif