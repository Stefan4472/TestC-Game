#ifndef ITEM_STACK_H
#define ITEM_STACK_H

#include <list>
#include <stdexcept>
#include "item.h"

using namespace std;

/*
A container for a "stack" of items (one or more of the same itemType), and is used
to represent inventory slots, or item drops. It is essentially a vector which
enforces the item's stack size.
*/
class ItemStack
{
	private:
		// items in the stack
		vector<Item*> items;
		// capacity of the stack for the given item
		int maxStackSize;

	public:
		// creates empty stack of ItemType::NONE
		ItemStack();
		// creates stack with the given Item
		ItemStack(Item* item);
		// creates stack with the given items. Throws runtime_error if stacksize
		// limit is violated, or if there are multiple item types in the list
		ItemStack(vector<Item*> items);

		// id of items in stack
		ItemType itemType;
		// itemType's texture
		TextureId itemTexture;

		// returns whether stack is empty (has no items)
		bool isEmpty();
		// return number of elements in the stack
		int size();
		// returns whether the given item could be added to the stack
		bool canAdd(Item* item);
		// attempts to add the given item to the stack.
		// returns whether it was successfully added
		bool addItem(Item* toAdd);
		// returns top item in the stack without removing it (can be null)
		Item* peekNext();
		// removes top item in the stack and returns it (can be null)
		Item* popNext();
};

#endif
