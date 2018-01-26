#include "attack.h"

Attack::Attack(SDL_Rect position, int dir, Sprite* attacker, Item* weapon)
{
	this->dir = dir;
	this->position = position;
	this->attacker = attacker;
	this->weapon = weapon;
}

void Attack::drawTo(SDL_Renderer* renderer)
{
	return;
}

SwordSwing::SwordSwing(SDL_Rect position, int dir, Sprite* attacker, Item* weapon) : Attack(position, dir, attacker, weapon)
{
	
}

void SwordSwing::update(int ms)
{
	finished = true;
}