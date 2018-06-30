#ifndef SWORD_SWING_ATTACK_H
#define SWORD_SWING_ATTACK_H

#include <SDL2/SDL.h>
#include "texture_atlas.h"
#include "attack.h"

//class Sprite;
//class Item;

class SwordSwing : public Attack
{
	public:
		SwordSwing(SDL_Rect position, Sprite* attacker);
		void update(int ms);
};

#endif