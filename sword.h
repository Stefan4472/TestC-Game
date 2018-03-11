#ifndef SWORD_H
#define SWORD_H

#include "texture_atlas.h"
#include "item.h"
#include "attack.h"
#include "sword_swing.h"

class Sword : public Item
{
	int swingDirection = 0;
	// sprite using the sword
	Sprite* actor = NULL;
	// damage done by the sword
	int damage = 10;
	
	public: // TODO: COOL-OFF PERIOD
		Sword();
		void use(Sprite* actor);
		Attack* getAttack();
};


#endif