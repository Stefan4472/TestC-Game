#ifndef CONSUMABLES_H
#define CONSUMABLES_H

//#include <SDL2/SDL2.h>
#include <stdexcept>
#include "texture_atlas.h"
#include "item.h"
#include "sprite_buff.h"
#include "health_buff.h"

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
		Consumable(ItemType itemType);
		// handle item being "consumed" by the given sprite
		void use(Sprite* actor);
		// returns buff created by using the Item
		SpriteBuff* getBuff();
		void getAndClearSounds(vector<Sound*> sounds);
};

#endif
