#ifndef SWORD_H
#define SWORD_H

#include "texture_atlas.h"
#include "item.h"
#include "attack.h"
#include "sword_swing.h"
#include "sprite.h"
#include "direction.h"

class Sword : public Item
{
	Direction swingDirection = Direction::NONE;
	// sprite using the sword
	Sprite* actor = NULL;
	// damage done by the sword
	int damage = 10;
	// attack created when sword was last swung
	Attack* lastAttack = NULL;

	public: // TODO: COOL-OFF PERIOD
		Sword();
		void use(Sprite* actor);
		Attack* getAttack();
		void getAndClearSounds(vector<Sound*> sounds);
};


#endif
