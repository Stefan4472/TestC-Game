#include "item_stack.h"

ItemStack::ItemStack()
{
	itemType = ItemType::NONE;
	maxStackSize = 0;
	itemTexture = Item::getTextureId(itemType);
}

ItemStack::ItemStack(Item* item)
{
	itemType = item->itemType;
	maxStackSize = Item::getStackSize(itemType);
	itemTexture = Item::getTextureId(itemType);
	addItem(item);
}

ItemStack::ItemStack(vector<Item*> items) // NOTE: BETTER WAY TO COPY??
{
	printf("Creating ItemStack from vector of items...");
	itemType = items[0]->itemType;
	maxStackSize = Item::getStackSize(itemType);
	itemTexture = Item::getTextureId(itemType);

	// add Items, one by one
	for (int i = 0; i < items.size(); i++)
	{
		if (!addItem(items[i]))
		{
			throw runtime_error("Cannot create stack from given vector");
		}
	}
}

bool ItemStack::isEmpty()
{
	return items.empty();
}

int ItemStack::size()
{
	return items.size();
}

bool ItemStack::canAdd(Item* item)
{
	// can be added if stack is empty or uninitialized, or if stack contains same
	// itemType and is below capacity
	return (item->itemType == itemType && items.size() < maxStackSize) ||
		itemType == ItemType::NONE || items.empty();
}

bool ItemStack::addItem(Item* toAdd)
{
	// matching ItemType, and size is below stack size: add
	if (toAdd->itemType == itemType && items.size() < maxStackSize)
	{
		items.push_back(toAdd);
		return true;
	}
	// no items in stack: set id to given item's id and add
	else if (itemType == ItemType::NONE || items.empty())
	{
		itemType = toAdd->itemType;
		itemTexture = Item::getTextureId(itemType);
		maxStackSize = Item::getStackSize(itemType);
		items.push_back(toAdd);
		return true;
	}
	else
	{
		return false;
	}
}

Item* ItemStack::peekNext()
{
	if (items.size())
	{
		return items[items.size() - 1];
	}
	else
	{
		return NULL;
	}
}

Item* ItemStack::popNext()
{
	if (items.size())
	{
		Item* item = items.back();
		items.pop_back();

		// set id to NONE if stack is now empty
		if (!items.size())
		{
			itemType = ItemType::NONE;
		}

		return item;
	}
	else
	{
		return NULL;
	}
}

void ItemStack::clearItems()
{
	itemType = ItemType::NONE;
	itemTexture = TextureId::TEXTURE_NONE;
	items.clear(); // TODO: NEED TO CLEAR THE ITEMS VECTOR?
	maxStackSize = 0;
}

void ItemStack::copyTo(ItemStack* other)
{
	other->itemType = itemType;
	other->itemTexture = itemTexture;
	other->maxStackSize = maxStackSize;
	other->items.resize(items.size());
	for (int i = 0; i < items.size(); i++)
	{
		other->items[i] = items[i];
	}
}
