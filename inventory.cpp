#include "inventory.h"

Inventory::Inventory(Sprite* owner, int capacity)
{
	this->owner = owner;
	hotbarSize = 10;
	// fill hotbar
	for (int i = 0; i < hotbarSize; i++)
	{
		hotbar.push_back(new ItemStack());
	}
	inventorySize = capacity;
	// fill inventory
	for (int i = 0; i < inventorySize; i++) // TODO: MORE EFFICIENT
	{
		inventory.push_back(new ItemStack());
	}
	inHandIndex = 0;
}

bool Inventory::addItem(Item* item)
{
	printf("Adding %s to Inventory...\n", item->getName());
	// attempt to add to next hotbar slot TODO: MORE EFFICIENT ALGORITHM (CONSTANT TIME?)
	for (int i = 0; i < hotbarSize; i++) 
	{
		if (hotbar[i]->attemptAdd(item))
		{
			// check if need to update inHandIndex
			if (i == inHandIndex && hotbar[i]->size() == 1)
			{
				owner->onInHandItemChanged(hotbar[i]->peekNext());		
			}
			return true;
		}
	}
	for (int i = 0; i < inventorySize; i++)
	{
		if (inventory[i]->attemptAdd(item))
		{
			return true;
		}
	}
	// no available slot found: couldn't add item
	return false;
}

Item* Inventory::getInHand()
{
	return hotbar[inHandIndex]->peekNext();
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
	// throw punch
	else if (owner)
	{
		printf("Punching!\n");
		resultingAttack = new Punch(owner->getRightHandPosition(), owner->facingDir, owner);
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
	// cycle to the right, wrapping around
	inHandIndex = (inHandIndex + 1) % hotbarSize;
	owner->onInHandItemChanged(hotbar[inHandIndex]->peekNext());	
}

void Inventory::cycleInHandBck()
{
	// cycle to the left, wrapping around
	inHandIndex = inHandIndex ? inHandIndex - 1 : hotbarSize - 1; 	
	owner->onInHandItemChanged(hotbar[inHandIndex]->peekNext());	
}

Item* Inventory::removeInHand()
{
	if (hotbar[inHandIndex]->size())
	{
		Item* in_hand = hotbar[inHandIndex]->popNext();
		printf("Removed %s from Inventory\n", in_hand->getName());
		
		// handle special case: dropped last item. Notify listener 
		if (!hotbar[inHandIndex]->size())
		{
			owner->onInHandItemChanged(NULL);	
		}
		return in_hand;
	}
	return NULL;
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