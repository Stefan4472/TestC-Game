#include "inventory.h"

bool Inventory::addItem(Item* item)
{
	printf("Adding Item to Inventory...\n");
	if (numItems == capacity)
	{
		printf("Inventory full! Not today\n");
		return false;
	}
	items[numItems] = item;
	numItems++;
	printf("Added! Now at %d items\n", numItems);
	return true;
}