#include "inventory.h"

bool Inventory::addItem(Item* item)
{
	printf("Adding Item to Inventory...\n");
	if (numItems == capacity)
	{
		printf("Inventory full! Not today\n");
		return false;
	}
	items[numItems] = item;
	numItems++;
	printf("Added! Now at %d items\n", numItems);
	return true;
}

void Inventory::drawTo(SDL_Surface* screenSurface, TextureAtlas* textureAtlas)
{
	for (int i = 0; i < numItems; i++) 
	{
		items[i]->drawToInventory(screenSurface, SDL_Rect{0, 0, 0, 0});
	}
}