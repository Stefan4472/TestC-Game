#include "attack.h"

Attack::Attack(SDL_Rect position, int dir, Sprite* attacker, Item* weapon)
{
	this->dir = dir;
	this->position = position;
	this->attacker = attacker;
	this->weapon = weapon;
}

void Attack::drawToMap(SDL_Renderer* renderer, TextureAtlas* textureAtlas, float offsetX, float offsetY)
{
	return;
}