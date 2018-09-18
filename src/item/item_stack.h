#ifndef ITEM_STACK_H
#define ITEM_STACK_H

#include <vector>
#include <stdexcept>
#include "item.h"

/*
The itemStack is a container for one or more of the same itemType, and is used
to represent inventory slots, or item drops. It is essentially a vector which
enforces the item's stack size.
*/
class ItemStack
{
	private:
		// items in the stack
		std::vector<Item*> items;
		// capacity of the stack for the given item
		int capacity = 0;

	public:
		// creates empty stack
		ItemStack();
		// creates stack with the given Item
		ItemStack(Item* item);
		// creates stack with the given items. Throws runtime_error if stacksize
		// limit is violated, or if there are multiple item types in the list
		ItemStack(std::vector<Item*> items);

		// id of items in stack
		ItemType itemId = ItemType::NONE;
		// returns whether stack is empty (has no items)
		bool isEmpty();
		// return number of elements in the stack
		int size();
		// returns whether the given item could be added to the stack
		bool canAdd(Item* item);
		// attempts to add given item to this stack.
		// returns whether it was successfully added
		bool addItem(Item* toAdd);
		// returns top item in the stack without removing it (can be null)
		Item* peekNext();
		// removes top item in the stack and returns it (can be null)
		Item* popNext();
};

#endif
