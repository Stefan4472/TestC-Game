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

Consumable::Consumable(ItemType itemType) : Item(itemType)
{
	switch (itemType)
	{
		case ItemType::BREAD_LOAF:
		case ItemType::CHICKEN_LEG:
		case ItemType::BEER_MUG:
		case ItemType::GREEN_POTION:
			break;

		default:
			throw runtime_error("Invalid itemType");
	}
}

void Consumable::use(Sprite* actor)
{
	used = true;
}

SpriteBuff* Consumable::getBuff()
{
	if (used && !buffConsumed)
	{
		// set consumed flag to true, and allow item to be destroyed
		buffConsumed = true;
		destroy = true;

		// return buff depending on ItemType
		// switch (itemType)
		// {
		// 	case ItemType::BREAD_LOAF:
		// 		return new HealthBuff(BREAD_HEALING_HP, BREAD_HEALING_MS, ); // TODO
		//
		// 	case ItemType::CHICKEN_LEG:
		// 		return new HealthBuff(CHICKENLEG_HEALING_HP, CHICKENLEG_HEALING_MS, );
		//
		// 	case ItemType::BEER_MUG:
		// 		return new HealthBuff(BEERMUG_HEALING_HP, BEERMUG_HEALING_MS, );
		//
		// 	case ItemType::GREEN_POTION:
		// 		return new HealthBuff(GREENPOTION_HEALING_HP, GREENPOTION_HEALING_MS, )
		//
		// 	default:
		// 		throw runtime_error("Invalid itemType. This should never happen");
		// }
		return NULL; // TODO: BUFFS
	}
}

void Consumable::getAndClearSounds(vector<Sound*> sounds)
{
	return;
}
