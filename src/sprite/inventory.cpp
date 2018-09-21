#include "inventory.h"

Inventory::Inventory(Sprite* owner, int rows, int cols, int hotbarSize,
	InventoryListener* listener))
{
	this->owner = owner;
	mainInvRows = rows;
	mainInvCols = cols;
	this->hotbarSize = hotbarSize;
	inventoryListener = listener;

	inHandIndex = 0;

	// set up datastructures
	hotbarItems.resize(hotbarSize);

	mainInvItems.resize(mainInvRows);
	for (int i = 0; i < mainInvRows; i++)
	{
		mainInvItems[i].resize(cols);
	}

	for (int i = 0; i < mainInvRows; i++)
	{
		for (int j = 0; j < mainInvCols; j++)
		{
			emptyMainSlots.push_back(InvCoordinate(i, j, false));
		}
	}

	for (int j = 0; j < hotbarSize; j++)
	{
		emptyHotbarSlots.push_back(InvCoordinate(0, j, true));
	}
}

void Inventory::setListener(InventoryListener* listener)
{
	inventoryListener = listener;
}

ItemStack* Inventory::addStack(ItemStack* stack, int row, int col, bool hotbar)
{
	ItemStack* to_replace = NULL;

	if (hotbar)
	{
		if (col < 0 || col >= hotbarSize)
		{
			throw runtime_error("Hotbar index out of bounds");
		}
		to_replace = hotbar[col]; // TODO: COPY ITEMS IN?
		hotbar[col] = stack;
	}
	else
	{
		if (col < 0 || col >= mainInvCols || row < 0 || row >= mainInvRows))
		{
			throw runtime_error("Main Inventory index out of bounds");
		}
		to_replace = mainInvItems[row][col];
		mainInvItems[row][col] = stack;
	}

	return to_replace;
}

bool Inventory::autoAddStack(ItemStack* stack) // TODO: DELETE STACK IF EMPTIED?
{
	// first, attempt to fill in any matching stacks in hotbar, and inventory
	unordered_map<ItemType, list<InvCoordinate>>::iterator map_iter =
		hotbarMappings.find(stack->itemType);

	// found at least one hotbar slot of same type
	if (iterator != hotbarMappings.end())
	{
		list<InvCoordinate>::const_iterator hotbar_iterator = map_iter->second.begin();
		// TODO: REMEMBER, THIS RETURNS INVCOORDINATES
		while (!stack->isEmpty() && hotbar_iterator != map_iter->second.end())
		{
			while (!stack->isEmpty() && hotbar_iterator->canAdd(stack->peekNext()))
			{
				hotbar_iterator->addItem(stack->popNext());
			}
			map_iter++;
		}
	}

	// attempt to fill in an empty hotbar slot
	if (!stack->isEmpty() && !emptyHotbarSlots.empty())
	{
		InvCoordinate empty_slot = emptyHotbarSlots.front();
		// TODO: COPY OVER ITEMS FROM STACK INTO EMPTY SLOT
	}
	// TODO: DO THE SAME FOR MAIN INVENTORY
	return stack->isEmpty();
}


ItemStack* Inventory::rmvStack(int row, int col, bool hotbar)
{
	ItemStack* copied = NULL;

	if (hotbar)
	{
		if (col < 0 || col >= hotbarSize)
		{
			throw runtime_error("Hotbar index out of bounds");
		}
		hotbarItems[col]->copyTo(copied);
		hotbarItems[col] = NULL;
	}
	else
	{
		if (col < 0 || col >= mainInvCols || row < 0 || row >= mainInvRows))
		{
			throw runtime_error("Main Inventory index out of bounds");
		}
		mainInvItems[row][col]->copyTo(copied);
		mainInvItems[row][col] = NULL;
	}
	return copied;
}

void Inventory::swapStacks(int row, int col, bool hotbar, int swapRow,
	int swapCol, bool swapHotbar)
{
	ItemStack* temp = NULL;
	// TODO: RANGE CHECK
	// TODO: GETTER METHOD
	ItemStack* stack_1, stack_2;
	stack_1->copyTo(temp);
	stack_2->copyTo(stack_1);
	temp->copyTo(stack_2);
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
		printf("Inventory: Calling use of in_hand, which is a %s\n",
			Item::getName(in_hand->itemType).c_str());
		in_hand->use(owner);

		// collect results
		resultingAction = in_hand->getAction();
		resultingBuff = in_hand->getBuff();
		resultingAttack = in_hand->getAttack();

		// destroy item if requested
		if (in_hand->destroy)
		{
			printf("Inventory: In-hand item requested to be destroyed\n");
			hotbarItems[inHandIndex]->popNext();
			delete in_hand;

			if (hotbarItems[inHandIndex]->isEmpty())
			{
				// TODO: TRIGGER UPDATE OF INHAND LISTENER
			}
		}
	}
	// throw punch if no item in hand
	else if (owner)
	{
		printf("Punching!\n");
		resultingAttack = new Punch(owner->getRightHandPosition(), owner->facingDir, owner);
	}
}

void Inventory::loadInHand()
{
	Item* in_hand = getInHand();
	if (in_hand)
	{
		printf("Reloading %s\n", Item::getName(in_hand->itemType).c_str());
		ItemType ammo_type = Item::getAmmunitionType(in_hand->itemType);
		if (ammo_type != ItemType::NONE)
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

ItemStack* Inventory::dropInHand()  /// TODO: RETURN SHOULD BE ITEM*
{
	// ItemStack* in_hand_copy = NULL;
	// hotbarItems[inHandIndex]->copyTo(in_hand_copy);
	// hotbarItems[inHandIndex]->clearItems(); // TODO: CLEAR METHOD AND CALL LISTENER
	// return in_hand_copy;
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

SpriteAction* Inventory::getAction()
{
	SpriteAction* action = resultingAction;
	resultingAction = NULL;
	return action;
}

SpriteBuff* Inventory::getBuff()
{
	SpriteBuff* buff = resultingBuff;
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

// Window* Inventory::getWindow(SDL_Renderer* renderer, TextureAtlas* textureAtlas, FontAtlas* fontAtlas)
// {
// 	// calculate number of rows and columns of items (each row has 10 items)
// 	int rows = capacity < 10 ? 1 : capacity / 10;
// 	int cols = capacity < 10 ? capacity : 10;
//
// 	Window* window = new Window(cols * 32, rows * 32, 640, 480);// todo: know screen width and height, or find a better way
//
// 	for (int i = 0; i < items.size(); i++)
// 	{
// 		int row = i / 10;
// 		int col = i % 10;
//
// 		ImageButton* item_btn = new ImageButton(i, SDL_Rect { col * 32, row * 32, 32, 32 }, textureAtlas, fontAtlas);
// 		item_btn->setImage(items[i]->textureId);
// 		item_btn->setHint(renderer, items[i]->name.c_str());
//
// 		window->addWidget(item_btn);
// 	}
// 	return window;
// }

void Inventory::drawDebugTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas,
	FontAtlas* fontAtlas)
{

}
