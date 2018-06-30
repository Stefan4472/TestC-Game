#include "attack.h"

Attack::Attack(SDL_Rect position, Sprite* attacker)
{
	this->position = position;
	this->attacker = attacker;
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