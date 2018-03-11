#include "item_stack.h"

ItemStack::ItemStack()
{

}

ItemStack::ItemStack(Item* item)
{
	itemId = item->itemType;
	capacity = item->stackSize;
	items.push_back(item);
}

ItemStack::ItemStack(int itemId, int quantity)
{
	this->itemId = itemId;
	// enforce stack size limit
	capacity = (quantity > getStackSize(itemId) ? getStackSize(itemId) : quantity);
	// create and add items to stack
	for (int i = 0; i < capacity; i++) 
	{
		items.push_back(new Item(itemId));
	}
}

bool ItemStack::isEmpty()
{
	return items.size() == 0;
}

int ItemStack::size()
{
	return items.size();
}

bool ItemStack::attemptAdd(Item* toAdd)
{
	// no items in stack: set id to given item's id and add
	if (itemId == -1)
	{
		itemId = toAdd->itemType;
		capacity = toAdd->stackSize;
		items.push_back(toAdd);
		return true;
	}
	else if (toAdd->itemType == itemId && items.size() < capacity)
	{
		items.push_back(toAdd);
		return true;
	}
	return false;
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
		return item;
	}
	else
	{
		return NULL;
	}
}