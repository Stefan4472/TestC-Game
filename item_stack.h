#ifndef ITEM_STACK_H
#define ITEM_STACK_H

#include <vector>
#include "item.h"

// The item stack represents items in an inventory slot, which can stack.

class ItemStack
{
	// items in the stack
	std::vector<Item*> items;
	// capacity of the stack for the given item
	int capacity = 0;
	
	public:
		// creates empty stack
		ItemStack();
		// creates stack with given Item*
		ItemStack(Item* item);
		// creates stack with given number of Items specified by id. Enforces stack size limits!!
		ItemStack(int itemId, int quantity);
		
		// id of items in stack
		int itemId = -1;
		// returns whether stack is empty (has no items)
		bool isEmpty();
		// return number of elements in the stack
		int size();
		// attempts to add given item to the stack. Must match itemId and can't exeed stack size.
		bool attemptAdd(Item* toAdd);
		// returns next item in the stack without removing it (can be null)
		Item* peekNext();
		// removes next item in the stack and returns it (can be null)
		Item* popNext();
		// draws item icon to given position, and draws quantity (if > 1)
		//void 
	
};

#endif