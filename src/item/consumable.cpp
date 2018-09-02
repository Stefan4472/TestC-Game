#include "consumable.h"

// healing amount and time definitions
const int BREAD_HEALING_HP = 10;
const int BREAD_HEALING_MS = 1000;
const int CHICKENLEG_HEALING_HP = 35;
const int CHICKENLEG_HEALING_MS = 2000;
const int BEERMUG_HEALING_HP = 15;
const int BEERMUG_HEALING_MS = 500;
const int GREENPOTION_HEALING_HP = 60;
const int GREENPOTION_HEALING_MS = 100;

Consumable::Consumable(int itemType) : Item(itemType)
{
	switch (itemType)
	{
		case ITEM_BREAD_LOAF:
		case ITEM_CHICKEN_LEG:
		case ITEM_BEER_MUG:
		case ITEM_GREEN_POTION:
			break;

		default:
			throw runtime_error("Invalid itemType");
	}
}

void Consumable::use(Sprite* actor)
{
	used = true;
}

SpriteAction* Consumable::getBuff()
{
	if (used && !buffConsumed)
	{
		// set consumed flag to true, and allow item to be destroyed
		buffConsumed = true;
		destroy = true;

		// return buff depending on ItemType
		switch (itemType)
		{
			case ITEM_BREAD_LOAF:
				return new ; // TODO

			case ITEM_CHICKEN_LEG:
				return new;

			case ITEM_BEER_MUG:
				return new;

			case ITEM_GREEN_POTION:
				return new;
				
			default:
				throw runtime_error("Invalid itemType. This should never happen");
		}
	}
}
