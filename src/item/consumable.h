#ifndef CONSUMABLES_H
#define CONSUMABLES_H

//#include <SDL2/SDL2.h>
#include "texture_atlas.h"
#include "item.h"
#include "sprite_action.h"
#include "health_regen_action.h"

// A consumable is a type of Item that, when used, gives the consuming sprite a buff (via an SpriteAction*) and ceases to exist.
// The only differences between consumables being their buffs, a Consumable is defined by the Item is represents. It may 
// be of type ITEM_BREAD_LOAF, ITEM_CHICKEN_LEG, ITEM_BEER_MUG, OR ITEM_GREEN_POTION. Other definitions may cause Segfaults or undefined 
// behavior.

// HP healed by each item when consumed
const static int BREAD_HEALING = 10;
const static int CHICKENLEG_HEALING = 35;
const static int BEERMUG_HEALING = 15;
const static int GREENPOTION_HEALING = 60; 

class Consumable : public Item // TODO: IS IT WORTH CREATING A NEW CLASS??
{
	// amount healed
	int healValue = 0;
	
	public:
		Consumable(int itemType);
		void use(Sprite* actor);
		// returns buff created by using the Item
		SpriteAction* getBuff();
};

#endif