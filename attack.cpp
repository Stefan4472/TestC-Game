#include "attack.h"

Attack::Attack(SDL_Rect position, int dir, Sprite* attacker, Item* weapon)
{
	this->dir = dir;
	this->position = position;
	this->attacker = attacker;
	this->weapon = weapon;
}

void Attack::handleSpriteCollision()
{
	finished = true;
}

void Attack::handleObjectCollision()
{
	finished = true;	
}

SpriteAction* Attack::getActionOnSprite(Sprite* sprite)
{
	return NULL;
}

void Attack::drawToMap(SDL_Renderer* renderer, TextureAtlas* textureAtlas, float offsetX, float offsetY)
{
	return;
}