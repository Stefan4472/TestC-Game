#include "inventory.h"

Inventory::Inventory(int capacity)
{
	this->capacity = capacity;
}

bool Inventory::addItem(Item* item)
{
	printf("Adding %s to Inventory...\n", item->getName());
	if (items.size() == capacity)
	{
		printf("Inventory full! Not today\n");
		return false;
	}
	items.push_back(item);
	printf("Added! Now at %d items\n", items.size());
	return true;
}

void Inventory::drawTo(SDL_Surface* screenSurface, TextureAtlas* textureAtlas)
{
	for (int i = 0; i < items.size(); i++) 
	{
		items[i]->drawToInventory(screenSurface, SDL_Rect{0, 0, 0, 0});
	}
}

Window* Inventory::getWindow()
{
	//return new PauseDialog(SDL_Rect { 100, 100, 200, 200 }, SDLK_e);
	return NULL;
}