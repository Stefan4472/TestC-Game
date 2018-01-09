#ifndef WEAPON_H
#define WEAPON_H

#include "texture_atlas.h"
#include "item.h"
#include "attack.h"

// A weapon is a type of Item that can be used to create an Attack. A Weapon either has a durability
// limit (number of times it can be used TODO: OR DAMAGE IT CAN INFLICT?) or a requirement that it
// have ammunition. 

class Weapon : public Item
{
	// amount of damage done
	int damage = 0;
	
	public:
		Weapon(int itemType, float x, float y, TextureAtlas* textureAtlas);
		// returns Attack created by using the Weapon
		Attack* use();
};
#endif