#include "item_util.h"

ItemStack* ItemUtil::createStack(ItemType itemType, int quantity)
{
	printf("ItemUtil: Creating %d Items with Id %d\n", quantity, itemId);

  // bound quantity to stack size of requested items
	quantity = (quantity > getStackSize(itemId) ? getStackSize(itemId) : quantity);

	ItemStack* stack = new ItemStack();

	switch (itemType)
	{
		// consumables
		case ItemType::BREAD_LOAF:
		case ItemType::CHICKEN_LEG:
		case ItemType::BEER_MUG:
		case ItemType::GREEN_POTION:
			for (int i = 0; i < quantity; i++)
			{
				stack->addItem(new Consumable(itemId));
			}
			break;

    // guns
		case ItemType::PISTOL:
		case ItemType::SHOTGUN:
		case ItemType::TOMMYGUN:
			for (int i = 0; i < quantity; i++)
			{
				stack->addItem(new Gun(itemId));
			}
			break;

		case ItemType::PISTOL_AMMO:
		case ItemType::SHOTGUN_AMMO:
		case ItemType::RIFLE_AMMO:
			for (int i = 0; i < quantity; i++)
			{
				stack->addItem(new Bullet(itemType));
			}
			break;

		case ItemType::SCROLL:
			break;

		case ItemType::SWORD:
			for (int i = 0; i < quantity; i++)
			{
        stack->addItem(new Sword());
			}
			break;

		default:
      throw runtime_error("The given ItemType was not handled properly");
	}

	return stack;
}
