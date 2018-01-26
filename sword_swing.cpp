#include "sword_swing.h"

SwordSwing::SwordSwing(SDL_Rect position, int dir, Sprite* attacker, Item* weapon) : Attack(position, dir, attacker, weapon)
{
	damage = 10;
}

void SwordSwing::update(int ms)
{
	finished = true;
}
