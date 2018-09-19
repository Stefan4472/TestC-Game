#ifndef ITEM_DROP_H
#define ITEM_DROP_H

#include <SDL2/SDL.h>
#include "item.h"
#include "item_stack.h"

/*
An ItemDrop is a wrapper to an ItemStack that is currently lying on the map
and can be picked up. It has (x,y) coordinates relative to the top-left of the
chunk it is in. Picking up mechanics must be handled by the game engine.
This is meant to be a very simple wrapper.
*/
class ItemDrop
{

	private:
		// stack of items in the drop
		ItemStack* items = NULL;

	public:
		// ItemType this drop contains
		ItemType itemType = ItemType::NONE;
		// coordinates relative to chunk top-left TODO: COULD THESE BE UNSIGNED CHARS?
		int x, y;

		// wraps Item in an ItemStack and sets coordinates
		ItemDrop(Item* item, int x, int y);
		// wraps ItemStack and sets coordinates
		ItemDrop(ItemStack* itemStack, int x, int y);

		// returns ItemStack contained by the drop
		ItemStack* getStack();  // TODO: CONSUMESTACK METHOD?

		// draws item drop to map, given coordinates that its chunk starts at.
		// will draw the item's texture at (chunkStartX + x, chunkStartY + y)
		void drawToMap(SDL_Renderer* renderer, TextureAtlas* textureAtlas,
			int chunkStartX, int chunkStartY);

	// prepares for destruction: sets ItemStack to NULL. The ItemStack itself must
		// be
		//~ItemStack();
};

#endif
