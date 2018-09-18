#ifndef ITEM_DROP_H
#define ITEM_DROP_H

#include <SDL2/SDL.h>
#include "item.h"
#include "item_stack.h"

/*
An ItemDrop is a wrapper to an ItemStack that is currently lying on the map
and can be picked up. The ItemDrop has a rectangular hitbox, which allows it
to be picked up.
*/
class ItemDrop {

	private:
		// stack of items in the drop
		ItemStack* items = NULL;
		// sets top-left and right coordinates of drop
		void setPosition(float x, float y);

	public:
		// width and height (px) of an item drop hitbox
		const int HITBOX_WIDTH = 32;
		const int HITBOX_HEIGHT = 32;

		// defines position of Item on the map
		SDL_Rect hitbox;

		// creates drop from Item and places it at the given map coordinates.
		// the Item is wrapped in an ItemStack first.
		ItemDrop(Item* item, float x, float y);
		// creates drop from existing ItemStack, and map coordinates
		ItemDrop(ItemStack* itemStack, float x, float y);

		// returns ItemStack contained by the drop
		ItemStack* getStack();

		// draws item drop to map (uses position)
		void drawToMap(SDL_Renderer* renderer, TextureAtlas* textureAtlas,
			int chunkStartX, int chunkStartY);

	// prepares for destruction: sets ItemStack to NULL. The ItemStack itself must
		// be
		//~ItemStack();
};

#endif
