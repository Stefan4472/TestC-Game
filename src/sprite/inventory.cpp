#include "inventory.h"

Inventory::Inventory(Sprite* owner, int rows, int cols, int hotbarSize,
	InventoryListener* listener)
{
	this->owner = owner;
	mainInvRows = rows;
	mainInvCols = cols;
	this->hotbarSize = hotbarSize;
	inventoryListener = listener;

	inHandIndex = 0;

	// set up datastructures
	hotbarItems.resize(hotbarSize);
	for (int j = 0; j < hotbarSize; j++)
	{
		hotbarItems[j] = new ItemStack();
		emptyHotbarSlots.push_back(InvCoordinate(0, j, true));
	}

	mainInvItems.resize(mainInvRows);
	for (int i = 0; i < mainInvRows; i++)
	{
		mainInvItems[i].resize(mainInvCols);
	}

	for (int i = 0; i < mainInvRows; i++)
	{
		for (int j = 0; j < mainInvCols; j++)
		{
			mainInvItems[i][j] = new ItemStack();
			emptyMainSlots.push_back(InvCoordinate(i, j, false));
		}
	}
}

void Inventory::rangeCheck(int row, int col, bool hotbar)
{
	if (hotbar && (row != 0 || col < 0 || col >= hotbarSize))
	{
		throw runtime_error("Hotbar index out of bounds");
	}
	else if (row >= mainInvRows || col >= mainInvCols || row < 0 || col < 0)
	{
		throw runtime_error("Main Inventory index out of bounds");
	}
}

void Inventory::setListener(InventoryListener* listener)
{
	inventoryListener = listener;
}

ItemStack* Inventory::getStack(InvCoordinate stackCoord)
{
	// assert InvCoordinate is valid
	rangeCheck(stackCoord.row, stackCoord.col, stackCoord.hotbar);

	if (stackCoord.hotbar)
	{
		return hotbarItems[stackCoord.col];
	}
	else
	{
		return mainInvItems[stackCoord.row][stackCoord.col];
	}
}

ItemStack* Inventory::addStack(ItemStack* stack, int row, int col, bool hotbar)
{
	// assert coordinate is valid
	rangeCheck(row, col, hotbar);

	ItemStack* to_replace = NULL;

	if (hotbar)
	{
		to_replace = hotbarItems[col];
		hotbarItems[col] = stack;
	}
	else
	{
		to_replace = mainInvItems[row][col];
		mainInvItems[row][col] = stack;
	}

	return to_replace;
}

bool Inventory::autoAddStack(ItemStack* stack)
{
	// first, attempt to fill in any matching stacks in hotbar
	unordered_map<ItemType, list<InvCoordinate>>::const_iterator map_iter =
		hotbarMappings.find(stack->itemType);

	// found at least one hotbar slot of same type
	if (map_iter != hotbarMappings.end())
	{
		list<InvCoordinate> slot_matches = map_iter->second;
		list<InvCoordinate>::const_iterator hotbar_iterator = slot_matches.begin();
		// TODO: REMEMBER, THIS RETURNS INVCOORDINATES

		// iterate over InvCoordinates that have the given ItemType
		while (!stack->isEmpty() && hotbar_iterator != slot_matches.end())
		{
			// retrieve the stack at the specified InvCoordinate
			ItemStack* found_stack = getStack(*hotbar_iterator);

			// loop while the stack at the InvCoordinate can accept items
			while (!stack->isEmpty() && found_stack->canAdd(stack->peekNext()))
			{
				found_stack->addItem(stack->popNext());
			}
			hotbar_iterator++;
		}
	}

	// TODO; AUTO-ADD TO MAIN INVENTORY

	// attempt to fill in an empty hotbar slot
	if (!stack->isEmpty() && !emptyHotbarSlots.empty())
	{
		InvCoordinate empty_slot = emptyHotbarSlots.front();
		// copy contents to requested stack and clear
		stack->copyTo(getStack(empty_slot));
		stack->clearItems();

		emptyHotbarSlots.pop_front();
	}

	// TODO: DO THE SAME FOR MAIN INVENTORY
	return stack->isEmpty();
}

ItemStack* Inventory::rmvStack(int row, int col, bool hotbar) // TODO: NEED TO UPDATE TRACKING STUFF
{
	// assert specified slot is valid
	rangeCheck(row, col, hotbar);

	ItemStack* copied = NULL;

	if (hotbar)
	{
		hotbarItems[col]->copyTo(copied);
		hotbarItems[col] = NULL;
	}
	else
	{
		mainInvItems[row][col]->copyTo(copied);
		mainInvItems[row][col] = NULL;
	}
	return copied;
}

void Inventory::swapStacks(int row, int col, bool hotbar, int swapRow,
	int swapCol, bool swapHotbar)
{
	// assert indexes are in range
	rangeCheck(row, col, hotbar);
	rangeCheck(swapRow, swapCol, swapHotbar);

	// retrieve the stacks
	ItemStack* stack_1 = getStack(InvCoordinate(row, col, hotbar));
	ItemStack* stack_2 = getStack(InvCoordinate(swapRow, swapCol, swapHotbar));

	// perform the swap
	ItemStack* temp = NULL;
	stack_1->copyTo(temp);
	stack_2->copyTo(stack_1);
	temp->copyTo(stack_2);
}

Item* Inventory::getInHand()
{
	return hotbarItems[inHandIndex]->peekNext();
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
			// TODO: 
			// ItemStack* ammo_stack = getStack(ammo_type);
			// printf("Stack of %d pointer is %d\n", ammo_type, ammo_stack);
			// // feed ammunition to item, deleting it as it is used
			// while (ammo_stack && ammo_stack->size() && in_hand->load(ammo_stack->peekNext())) // TODO: WHAT IF GIVEN STACK DOESN'T FILL AMMO?
			// {
			// 	delete ammo_stack->popNext();
			// }
		}
	}
}

Item* Inventory::dropInHand()
{
	// only return something if the currently-selected hotbar stack has items
	if (hotbarItems[inHandIndex]->isEmpty())
	{
		return NULL;
	}
	else
	{
		Item* in_hand = hotbarItems[inHandIndex]->popNext();

		// handle special case: dropped last item. Notify listener
		if (inventoryListener && hotbarItems[inHandIndex]->isEmpty())
		{
			inventoryListener->onInHandItemChanged(NULL);
		}

		return in_hand;
	}
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
		inventoryListener->onInHandItemChanged(hotbarItems[inHandIndex]->peekNext());
	}
}

void Inventory::cycleInHandBck()
{
	// cycle to the left, wrapping around
	inHandIndex = inHandIndex ? inHandIndex - 1 : hotbarSize - 1;
	if (inventoryListener)
	{
		inventoryListener->onInHandItemChanged(hotbarItems[inHandIndex]->peekNext());
	}
}

void Inventory::drawHotbarTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas, FontAtlas* fontAtlas, int x, int y)
{
	for (int i = 0; i < hotbarSize; i++)
	{
		if (hotbarItems[i]->size())
		{
			textureAtlas->drawImg(renderer, hotbarItems[i]->itemTexture, x + i * 32, y);
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
	SDL_Rect outer_bounds = SDL_Rect { 0, 0, mainInvCols * 64, (mainInvRows + 1) * 64 };

	// draw filled gray background rectangle
	SDL_SetRenderDrawColor(renderer, 0xDD, 0xDD, 0xDD, 0xFF);
	SDL_RenderFillRect(renderer, &outer_bounds);

	int x, y;

	// draw main inventory items
	for (int i = 0; i < mainInvRows; i++)
	{
		x = 0;
		for (int j = 0; j < mainInvCols; j++)
		{
			textureAtlas->drawImg(renderer, mainInvItems[i][j]->itemTexture, x, y, false);
			x += 64;
		}
		y += 64;
	}

	x = 0;

	// draw hotbar items
	for (int j = 0; j < hotbarSize; j++)
	{
		textureAtlas->drawImg(renderer, hotbarItems[j]->itemTexture, x, y, false);
		x += 64;
	}
}
