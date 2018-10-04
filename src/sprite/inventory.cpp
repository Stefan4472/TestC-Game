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
		}
	}

	printf("Created inventory with %d rows, %d cols, and a hotbar of %d\n", rows, cols, hotbarSize);
}

void Inventory::rangeCheck(InvCoordinate slot)
{
	if (slot.hotbar && (slot.row != 0 || slot.col < 0 || slot.col >= hotbarSize))
	{
		throw runtime_error("Hotbar index out of bounds " +
			to_string(slot.row) + ", " + to_string(slot.col));
	}
	else if (!slot.hotbar && (slot.row >= mainInvRows || slot.col >= mainInvCols ||
		slot.row < 0 || slot.col < 0))
	{
		throw runtime_error("Main Inventory index out of bounds " +
			to_string(slot.row) + ", " + to_string(slot.col));
	}
}

void Inventory::setListener(InventoryListener* listener)
{
	inventoryListener = listener;
}

ItemStack* Inventory::getStack(InvCoordinate stackCoord)
{
	// assert InvCoordinate is valid
	rangeCheck(stackCoord);

	if (stackCoord.hotbar)
	{
		return hotbarItems[stackCoord.col];
	}
	else
	{
		return mainInvItems[stackCoord.row][stackCoord.col];
	}
}

void Inventory::setStack(InvCoordinate stackCoord, ItemStack* stack)
{
	// assert InvCoordinate is valid
	rangeCheck(stackCoord);

	if (stackCoord.hotbar)
	{
		hotbarItems[stackCoord.col] = stack;
	}
	else
	{
		mainInvItems[stackCoord.row][stackCoord.col] = stack;
	}
}

void Inventory::copyStackTo(InvCoordinate stackCoord, ItemStack* stack)
{
	// assert InvCoordinate is valid
	rangeCheck(stackCoord);

	if (stackCoord.hotbar)
	{
		stack->copyTo(hotbarItems[stackCoord.col]);
	}
	else
	{
		stack->copyTo(mainInvItems[stackCoord.row][stackCoord.col]);
	}
}

ItemStack* Inventory::addStack(ItemStack* stack, InvCoordinate slot)
{
	ItemStack* replaced = getStack(slot);
	setStack(slot, stack);
	return replaced;
}

bool Inventory::autoAddStack(ItemStack* stack)
{
	// track the first empty slot found, in case there is no other way for the
	// stack to fit
	bool empty_found = false;
	InvCoordinate first_empty_found(0, 0, false);

	// first, attempt to fill in any matching stacks in hotbar
	for (int j = 0; j < hotbarSize; j++)
	{
		if (hotbarItems[j]->isEmpty() && !empty_found)
		{
			empty_found = true;
			first_empty_found = InvCoordinate(0, j, true);
		}

		while (!stack->isEmpty() && hotbarItems[j]->itemType == stack->itemType &&
			hotbarItems[j]->canAdd(stack->peekNext()))
		{
			hotbarItems[j]->addItem(stack->popNext());
		}

		if (stack->isEmpty())
		{
			return true;
		}
	}

	// if stack still has items, attempt to add into mainInventory slots
	for (int i = 0; i < mainInvRows; i++)
	{
		for (int j = 0; j < mainInvCols; j++)
		{
			if (mainInvItems[i][j]->isEmpty() && !empty_found)
			{
				empty_found = true;
				first_empty_found = InvCoordinate(i, j, false);
			}

			while (!stack->isEmpty() && mainInvItems[i][j]->itemType == stack->itemType &&
				mainInvItems[i][j]->canAdd(stack->peekNext()))
			{
				mainInvItems[i][j]->addItem(stack->popNext());
			}

			if (stack->isEmpty())
			{
				return true;
			}
		}
	}

	// if stack is still not empty, try to assign it to the first empty slot found
	if (empty_found)
	{
		// copy stack items to it and clear them from original stack
		copyStackTo(first_empty_found, stack);
		stack->clearItems();
		return true;
	}
	else
	{
		return false;
	}
}

ItemStack* Inventory::rmvStack(InvCoordinate slot)
{
	// assert specified slot is valid
	rangeCheck(slot);
	printf("Inventory: Removing Stack\n");
	ItemStack* copied = new ItemStack();

	// TODO: USE GETSTACK()?
	if (slot.hotbar)
	{
		hotbarItems[slot.col]->copyTo(copied);
		hotbarItems[slot.col]->clearItems();
	}
	else
	{
		mainInvItems[slot.row][slot.col]->copyTo(copied);
		mainInvItems[slot.row][slot.col]->clearItems();
	}
	return copied;
}

void Inventory::swapStacks(InvCoordinate slot1, InvCoordinate slot2)
{
	// retrieve the stacks
	ItemStack* stack_1 = getStack(slot1);
	ItemStack* stack_2 = getStack(slot2);

	// perform the swap
	ItemStack temp;
	stack_1->copyTo(&temp);
	stack_2->copyTo(stack_1);
	temp.copyTo(stack_2);
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
			bool success = false;

			// check hotbar for stacks of the ammo type, and use them to reload
			for (int j = 0; j < hotbarSize; j++)
			{
				if (hotbarItems[j]->itemType == ammo_type)
				{
					while (!hotbarItems[j]->isEmpty())
					{
						Item* ammo = hotbarItems[j]->peekNext();
						bool loaded = in_hand->load(ammo); // TODO: CANLOAD() METHOD

						if (loaded)
						{
							hotbarItems[j]->popNext();
						}
						else
						{
							success = true;
							break;
						}
					}
				}
			}
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
	// TODO: FIX OUTER BOUNDS SO HOTBAR IS DRAWN CORRECTLY
	// draw filled gray background rectangle
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &outer_bounds);

	int x = 0, y = 0;

	// draw main inventory items
	for (int i = 0; i < mainInvRows; i++)
	{
		x = 0;
		for (int j = 0; j < mainInvCols; j++)
		{
			if (!mainInvItems[i][j]->isEmpty())
			{
				textureAtlas->drawImg(renderer, mainInvItems[i][j]->itemTexture, x, y, false);
			}
			x += 64;
		}
		y += 64;
	}

	x = 0;

	// draw hotbar items
	for (int j = 0; j < hotbarSize; j++)
	{
		if (!hotbarItems[j]->isEmpty())
		{
			textureAtlas->drawImg(renderer, hotbarItems[j]->itemTexture, x, y, false);
		}
		x += 64;
	}
}

int Inventory::saveToByteStream(char bytes[], int maxSize)
{
	int reqd_bytes = 300; // TODO: CALCULATE FULL SIZE

	bytes[0] = (char) mainInvRows;
	bytes[1] = (char) mainInvCols;
	// fill in bytes[2] later

	int start_index = 3;
	int stacks_written = 0;
	int save_index = 3;

	ItemStack* to_save = NULL;
	for (char i = 0; i < mainInvRows; i++)
	{
		for (char j = 0; j < mainInvCols; j++)
		{
			to_save = mainInvItems[i][j];

			if (!to_save->isEmpty())
			{
				bytes[save_index + 0] = char(to_save->itemType);
				bytes[save_index + 1] = char(to_save->size());
				bytes[save_index + 2] = i;
				bytes[save_index + 3] = j;
				stacks_written++;

				// calculate next save index
				save_index = start_index + 4 * stacks_written;
			}
		}
	}

	// now, set bytes[2]
	bytes[2] = stacks_written;

	// write hotbar, in-order
	bytes[save_index] = hotbarSize;
	save_index++;

	for (int j = 0; j < hotbarSize; j++)
	{
		bytes[save_index] = char(hotbarItems[j]->itemType);
		bytes[save_index + 1] = (char) hotbarItems[j]->size();
		save_index += 2;
	}
	return save_index + 1;
}

Inventory* Inventory::restoreFromByteStream(char bytes[], int numBytes)
{
	printf("Restoring Inventory...\n");
	// retrieve data on inventory size, and number of stacks saved
	int main_rows = bytes[0];
	int main_cols = bytes[1];
	int num_stacks = bytes[2];

	// calculate position of hotbarSize and retrieve
	int hotbar_size = bytes[3 + 4 * num_stacks];
	printf("%d rows, %d cols, %d stacks, hotbar %d\n", main_rows, main_cols,
		num_stacks, hotbar_size);
	// TODO: HOW TO RETRIEVE SPRITE OWNER?
	Inventory* inventory = new Inventory(NULL, main_rows, main_cols, hotbar_size);

	// retrieve stored stacks and add
	int start_index;
	for (int i = 0; i < num_stacks; i++)
	{
		start_index = 3 + 4 * i;
		ItemType item_type = ItemType(bytes[start_index]);
		int stack_size = bytes[start_index + 1];
		int stack_row = bytes[start_index + 2];
		int stack_col = bytes[start_index + 3];
		printf("Item %d: %d of %s at %d, %d\n", i, stack_size,
			Item::getName(item_type).c_str(), stack_row, stack_col);
		inventory->addStack(ItemUtil::createStack(item_type, stack_size),
			InvCoordinate(stack_row, stack_col, false));
	}

	// restore hotbar
	start_index = 3 + 4 * num_stacks + 1;
	for (int j = 0; j < hotbar_size; j++)
	{
		ItemType item_type = ItemType(bytes[start_index]);
		int stack_size = bytes[start_index + 1];
		printf("Hotbar %d: %d of %s\n", j, stack_size, Item::getName(item_type).c_str());
		inventory->addStack(ItemUtil::createStack(item_type, stack_size),
			InvCoordinate(0, j, true));
		start_index += 2;
	}
	printf("Finished restoring\n");
	return inventory;
}
