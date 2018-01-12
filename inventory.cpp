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

void Inventory::useInHand(SDL_Point handPos, int useDir)
{
	Item* in_hand = getInHand();
	if (in_hand)
	{
		printf("Inventory: Calling use of in_hand\n");
		in_hand->use(handPos, useDir);
		// collect results
		resultingAction = in_hand->getAction();
		resultingBuff = in_hand->getBuff();
		resultingAttack = in_hand->getAttack();
		// destroy item if requested
		if (in_hand->destroy)
		{
			printf("Inventory: In-hand item requested to be destroyed\n");
			removeInHand();
			delete in_hand;
		}
	}
}

Action* Inventory::getAction()
{
	Action* action = resultingAction;
	resultingAction = NULL;
	return action;
}

Action* Inventory::getBuff()
{
	Action* buff = resultingBuff;
	resultingBuff = NULL;
	return buff;
}

Attack* Inventory::getAttack()
{
	Attack* attack = resultingAttack;
	resultingAttack = NULL;
	return attack;
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

Item* Inventory::removeInHand()
{
	if (inHandIndex == -1)
	{
		return NULL;	
	} 
	else
	{
		Item* in_hand = items[inHandIndex];
		items.erase(items.begin() + inHandIndex);
		printf("Removed %s from Inventory\n", in_hand->getName());
		cycleInHandFwd();
		return in_hand;
	}
}

void Inventory::drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas)
{
	for (int i = 0; i < items.size(); i++) 
	{
		items[i]->drawToInventory(renderer, SDL_Rect{0, 0, 0, 0});
	}
}

Window* Inventory::getWindow()
{
	//return new PauseDialog(SDL_Rect { 100, 100, 200, 200 }, SDLK_e);
	return NULL;
}