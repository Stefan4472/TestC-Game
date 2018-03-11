#include "consumable.h"

Consumable::Consumable(int itemType) : Item(itemType)
{
	switch (itemType)
	{
		case ITEM_BREAD_LOAF:
			healValue = BREAD_HEALING;
			break;
			
		case ITEM_CHICKEN_LEG:
			healValue = CHICKENLEG_HEALING;
			break;
			
		case ITEM_BEER_MUG:
			healValue = BEERMUG_HEALING;
			break;
			
		case ITEM_GREEN_POTION:
			healValue = GREENPOTION_HEALING;
			break;
	}
}

void Consumable::use(Sprite* actor)
{
	destroy = true;
}

Action* Consumable::getBuff()
{
	return new HealthRegenAction(healValue, healValue * 100);	
}