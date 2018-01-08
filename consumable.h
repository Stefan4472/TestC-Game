#ifndef CONSUMABLES_H
#define CONSUMABLES_H

//#include <SDL2/SDL2.h>
#include "texture_atlas.h"
#include "item.h"
//#include "action.h"

// a consumable is a type of Item that, when used, ceases to exist, but gives the consuming sprite certain effects.

/*class Consumable : public Item
{
	
};*/

class BreadLoaf : public Item
{
	public:
		BreadLoaf(TextureAtlas* textureAtlas, float x, float y);
		//Action* use();
};

class BeerMug : public Item
{
	public:
		BeerMug(TextureAtlas* textureAtlas, float x, float y);
		//Action* use();
};
#endif