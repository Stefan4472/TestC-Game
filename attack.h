#ifndef ATTACK_H
#define ATTACK_H

#include <SDL2/SDL.h>
#include "constants.h"

class Sprite;
class Sword;

// An Attack is created by a Sprite. It has a direction it is exerted in, and a
// position where it occurs on the map, defined by a rect. It also has a pointer
// to the initiating Sprite, and a pointer to the weapon used.
class Attack
{	
	public:
		Attack(int dir, SDL_Rect position, Sprite* attacker, Sword* weapon, int damage);
		int dir = 0;
		int damage = 0;
		SDL_Rect position;
		Sprite* attacker = NULL;
		Sword* weapon = NULL;
};
#endif