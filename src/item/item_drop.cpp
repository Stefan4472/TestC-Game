#include "item_drop.h"

ItemDrop::ItemDrop(Item* item, float x, float y)
{
	printf("Creating ItemDrop from %s at %f, %f...", item->name.c_str(), x, y);
	items = new ItemStack(item);
	setPosition(x, y);
	printf("Done\n");
}

ItemDrop::ItemDrop(ItemStack* itemStack, float x, float y)
{
	printf("Creating ItemDrop from stack...");
	printf("%d", itemStack->size());
	//printf("Creating ItemDrop from stack %s with size %d at %f, %f...", itemStack->peekNext()->name.c_str(), itemStack->size(), x, y);
	items = itemStack;
	setPosition(x, y);
	printf("Done\n");
}

void ItemDrop::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

ItemStack* ItemDrop::getStack()
{
	return items;
}

void ItemDrop::drawToMap(SDL_Renderer* renderer, TextureAtlas* textureAtlas, int offsetX, int offsetY)
{
	textureAtlas->draw(renderer, getTextureId(items->itemId), position.x - offsetX, position.y - offsetY);
}