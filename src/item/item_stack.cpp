#include "item_stack.h"

ItemStack::ItemStack()
{

}

ItemStack::ItemStack(Item* item)
{
	itemId = item->itemId;
	capacity = item->stackSize;
	items.push_back(item);
}

ItemStack::ItemStack(std::vector<Item*> items) // NOTE: BETTER WAY TO COPY??
{
	printf("Creating ItemStack from vector of items...");
	itemId = items[0]->itemId;
	capacity = items[0]->stackSize;
	// copy items over to internal list
	for (int i = 0; i < items.size(); i++)
	{
		this->items.push_back(items[i]);
	}
	printf("Id %d Cap%d... Done\n", itemId, capacity);
}

bool ItemStack::isEmpty()
{
	return items.size() == 0;
}

int ItemStack::size()
{
	return items.size();
}

bool ItemStack::canAdd(Item* item)
{
	// can be added if stack is empty or uninitialized, or if stack contains same
	// itemType and is below capacity
	return (item->itemId == itemId && items.size() < capacity) ||
		itemId == ItemType::NONE || items.size() == 0;
}

bool ItemStack::addItem(Item* toAdd)
{
	if (toAdd->itemId == itemId && items.size() < capacity)
	{
		items.push_back(toAdd);
		return true;
	}
	// no items in stack: set id to given item's id and add
	else if (itemId == ItemType::NONE || items.size() == 0)
	{
		itemId = toAdd->itemId;
		capacity = toAdd->stackSize;
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
			itemId = ItemType::NONE;
		}
		
		return item;
	}
	else
	{
		return NULL;
	}
}
