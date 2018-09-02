#ifndef CONSUMABLES_H
#define CONSUMABLES_H

//#include <SDL2/SDL2.h>
#include <stdexcept>
#include "texture_atlas.h"
#include "item.h"
#include "sprite_action.h"
#include "health_regen_action.h"

// HP healed by each item when consumed, and time it takes for that healing to
// happen. Defined in consumable.cpp
const int BREAD_HEALING_HP;
const int BREAD_HEALING_MS;
const int CHICKENLEG_HEALING_HP;
const int CHICKENLEG_HEALING_MS;
const int BEERMUG_HEALING_HP;
const int BEERMUG_HEALING_MS;
const int GREENPOTION_HEALING_HP;
const int GREENPOTION_HEALING_MS;

/*
A consumable is a type of Item that, when used, gives the consuming sprite a
buff and ceases to exist. A Consumable is defined by the Item is represents.
It may be of type BREAD_LOAF, CHICKEN_LEG, BEER_MUG, OR GREEN_POTION.
Other ItemTypes passed in to the constructor will cause runtime_errors.
*/
class Consumable : public Item
{
	private:
		// whether the item has been used, or "consumed"
		bool used = false;
		// whether the buff for consuming the item has been retrieved via getBuff()
		bool buffConsumed = false;
		// TODO: SOUND EFFECT SUPPORT

	public:
		// create consumable of the given itemType
		Consumable(int itemType);
		// handle item being "consumed" by the given sprite
		void use(Sprite* actor);
		// returns buff created by using the Item
		SpriteAction* getBuff();
};

#endif
