#include "sword_swing.h"

SwordSwing::SwordSwing(SDL_Rect position, Sprite* attacker) : Attack(position, attacker)
{
	damage = 10;
}

void SwordSwing::update(int ms)
{
	finished = true;
}
