#include "attack.h"

Attack::Attack(int dir, SDL_Rect position, Sprite* attacker, Sword* weapon, int damage)
{
	this->dir = dir;
	this->position = position;
	this->attacker = attacker;
	this->weapon = weapon;
	this->damage = damage;
}