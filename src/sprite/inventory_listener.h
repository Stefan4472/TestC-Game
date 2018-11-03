#ifndef INVENTORY_LISTENER_H
#define INVENTORY_LISTENER_H

class Item;
class ItemStack;

/*
An InventoryListener is an interface that allows callbacks from an Inventory.
*/
class InventoryListener
{
	public:
		// user changes item currently equipped (in-hand). May be NULL if no item is
		// equipped in-hand
		virtual void onInHandItemChanged(Item* newItem) = 0;
		// user drops a stack
		virtual void onStackDropped(ItemStack* stack) = 0;
};

#endif
