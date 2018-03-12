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
	printf("Adding %s to Inventory...\n", item->name.c_str());
	ItemStack* receiver = getAvailStack(item);
	return receiver->addItem(item);
}

bool Inventory::addItemStack(ItemStack* stack) 
{
	printf("Adding ItemStack of %d %s to Inventory...\n", stack->size(), stack->peekNext()->name.c_str());
	// check if there's a slot that can take the given items
	ItemStack* receiver = getAvailStack(stack->peekNext());
	while (receiver && !receiver->addItemStack(stack))
	{
		if (stack->size())
		{
			receiver = getAvailStack(stack->peekNext());
		}
	}
	return stack->size() ? false : true;
}

Item* Inventory::getInHand()
{
	return hotbar[inHandIndex]->peekNext();
}

void Inventory::useInHand()
{
	Item* in_hand = getInHand();
	if (in_hand)
	{
		printf("Inventory: Calling use of in_hand\n");
		in_hand->use(owner);
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

ItemStack* Inventory::getItemStack(int id)
{
	// search hotbar for matches
	for (int i = 0; i < hotbarSize; i++)
	{
		if (hotbar[i]->itemId == id)
		{
			return hotbar[i];	
		}
	}
	// search inventory for matches
	for (int i = 0; i < inventorySize; i++)
	{
		if (inventory[i]->itemId == id)
		{
			return inventory[i];	
		}
	}
	return NULL;
}

ItemStack* Inventory::getAvailStack(Item* item)
{
	for (int i = 0; i < hotbarSize; i++)
	{
		if (hotbar[i]->canAdd(item))
		{
			return hotbar[i];
		}
	}
	for (int i = 0; i < inventorySize; i++)
	{
		if (inventory[i]->canAdd(item))
		{
			return inventory[i];
		}
	}
	return NULL;
}

void Inventory::loadInHand()
{
	Item* in_hand = getInHand();
	if (in_hand)
	{
		printf("Reloading %s\n", in_hand->name);
		int ammo_type = in_hand->ammunitionId;
		if (ammo_type)
		{
			ItemStack* ammo_stack = getItemStack(ammo_type);
			printf("Stack of %d pointer is %d\n", ammo_type, ammo_stack);
			// feed ammunition to item, deleting it as it is used
			while (ammo_stack && ammo_stack->size() && in_hand->load(ammo_stack->peekNext())) // TODO: WHAT IF GIVEN STACK DOESN'T FILL AMMO?
			{
				delete ammo_stack->popNext();	
			}
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
	// cycle to the right, wrapping around
	inHandIndex = (inHandIndex + 1) % hotbarSize;
	if (inventoryListener)
	{
		inventoryListener->onInHandItemChanged(hotbar[inHandIndex]->peekNext());	
	}
}

void Inventory::cycleInHandBck()
{
	// cycle to the left, wrapping around
	inHandIndex = inHandIndex ? inHandIndex - 1 : hotbarSize - 1; 	
	if (inventoryListener)
	{
		inventoryListener->onInHandItemChanged(hotbar[inHandIndex]->peekNext());	
	}
}

Item* Inventory::removeInHand()
{
	if (hotbar[inHandIndex]->size())
	{
		Item* in_hand = hotbar[inHandIndex]->popNext();
		printf("Removed %s from Inventory\n", in_hand->name);
		
		// handle special case: dropped last item. Notify listener 
		if (inventoryListener && !hotbar[inHandIndex]->size())
		{
			inventoryListener->onInHandItemChanged(NULL);	
		}
		return in_hand;
	}
	return NULL;
}

void Inventory::setListener(InventoryListener* listener)
{
	inventoryListener = listener;	
}

void Inventory::drawHotbarTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas, FontAtlas* fontAtlas, int x, int y)
{
	for (int i = 0; i < hotbarSize; i++)
	{
		if (hotbar[i]->size())
		{
			textureAtlas->draw(renderer, hotbar[i]->peekNext()->textureId, x + i * 32, y);	
		}
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