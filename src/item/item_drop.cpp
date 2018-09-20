#include "item_drop.h"

ItemDrop::ItemDrop(Item* item, int x, int y)
{
	items = new ItemStack(item);
	itemType = item->itemType;
	this->x = x;
	this->y = y;
}

ItemDrop::ItemDrop(ItemStack* itemStack, int x, int y)
{
	items = itemStack;
	itemType = itemStack->itemType;
	this->x = x;
	this->y = y;
}

ItemStack* ItemDrop::getStack()
{
	return items;
}

void ItemDrop::drawToMap(SDL_Renderer* renderer, TextureAtlas* textureAtlas,
	int chunkStartX, int chunkStartY)
{
	if (items)
	{
		textureAtlas->drawImg(renderer, items->itemTexture, chunkStartX + x, chunkStartY + y);
	}
}
