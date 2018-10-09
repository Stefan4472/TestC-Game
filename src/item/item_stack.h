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

	public:  // TODO: MAINTAIN SIZE COUNTER TO AVOID MAKING CALLS TO VECTOR'S SIZE() AND EMPTY()
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
		// attempts to combine this stack *into* the other stack. Returns whether
		// at least one item was added into the other stack
		bool combineInto(ItemStack* other);
		// splits this stack in half, and puts the other half into a new ItemStack.
		// returns an empty stack if this stack is empty. If this stack has one item,
		// puts the item in the newly-created split
		ItemStack* split();
		// returns top item in the stack without removing it (can be null)
		Item* peekNext();
		// removes top item in the stack and returns it (can be null)
		Item* popNext();
		// resets the stack to empty, with no ItemType. Does not delete any Items.
		void clearItems();
		// copies the Items contained in this stack to the other stack, OVERWRITING
		// the Items in the other stack. Does not delete any items.
		void copyTo(ItemStack* other);
		// debug string: "Stack of %d %s" (stack size, item name)
		string toString();
};

#endif
