#include "inventory.h"

Inventory::Inventory(Sprite* owner, int capacity)
{
	this->owner = owner;
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
		owner->onInHandItemChanged(items[0]);	
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
		in_hand->use(owner, handPos, useDir);
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

void Inventory::cycleInHandFwd()
{
	// cycle to the right, if more than one item in inventory
	if (items.size() > 1)
	{
		inHandIndex = (inHandIndex + 1) % items.size();
		
		owner->onInHandItemChanged(items[inHandIndex]);	
	}
}

void Inventory::cycleInHandBck()
{
	// cycle to the left, if more than one item in inventory
	if (items.size() > 1)
	{
		inHandIndex = inHandIndex ? inHandIndex - 1 : items.size() - 1; 
		
		owner->onInHandItemChanged(items[inHandIndex]);	
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
		
		// handle special case: dropped last item. Notify listener 
		if (items.size() == 0)
		{
			owner->onInHandItemChanged(items[inHandIndex]);	
		}
		return in_hand;
	}
}

Window* Inventory::getWindow(SDL_Renderer* renderer, TextureAtlas* textureAtlas, FontAtlas* fontAtlas)
{
	// calculate number of rows and columns of items (each row has 10 items)
	int rows = capacity < 10 ? 1 : capacity / 10;
	int cols = capacity < 10 ? capacity : 10;
	
	Window* window = new Window(cols * 32, rows * 32, 640, 480);// todo: know screen width and height, or find a better way
	
	for (int i = 0; i < items.size(); i++)
	{
		int row = i / 10;
		int col = i % 10;
		
		ImageButton* item_btn = new ImageButton(i, SDL_Rect { col * 32, row * 32, 32, 32 }, textureAtlas, fontAtlas);
		item_btn->setImage(items[i]->textureId);
		item_btn->setHint(renderer, items[i]->name.c_str());
		
		window->addWidget(item_btn);
	}
	return window;
}