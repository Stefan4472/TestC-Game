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
	// put item in hand, if it's the first
	if (items.size() == 1)
	{
		inHandIndex = 0;	
	}
	return true;
}

Item* Inventory::getInHand()
{
	return items.size() ? items[inHandIndex] : NULL;
}

Item* Inventory::cycleInHandFwd()
{
	// cycle inHandIndex one to the right, if there are items in inventory
	inHandIndex = items.size() ? (inHandIndex + 1) % items.size() : -1;
	return items.size() ? items[inHandIndex] : NULL; 	
}

Item* Inventory::cycleInHandBck()
{
	if (inHandIndex == -1 )
	{
		return NULL;	
	}
	else 
	{
		// cycle inHandIndex one to the left
		inHandIndex = inHandIndex ? inHandIndex - 1 : items.size() - 1; 
		return items[inHandIndex];
	}
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