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

SwordSwing::SwordSwing(SDL_Rect position, int dir, Sprite* attacker, Item* weapon) : Attack(position, dir, attacker, weapon)
{
	damage = 10;
}

void SwordSwing::update(int ms)
{
	finished = true;
}

Bullet::Bullet(SDL_Rect position, int dir, Sprite* attacker, Item* weapon) : Attack(position, dir, attacker, weapon)
{
	damage = 10;
	
	switch (dir)
	{
		case DIRECTION_RIGHT:
			dx = 3;
			break;
			
		case DIRECTION_LEFT:
			dx = -3;
			break;
			
		case DIRECTION_UP:
			dy = -3;
			break;
			
		case DIRECTION_DOWN:
			dy = 3;
			break;
	}	
}

void Bullet::update(int ms)
{
	// move bullet
	position.x += dx * ms;
	position.y += dy * ms;
}

void Bullet::drawToMap(SDL_Renderer* renderer, TextureAtlas* textureAtlas, float offsetX, float offsetY)
{
	printf("Offset x and y are %f, %f\n", offsetX, offsetY);
	printf("Drawing bullet to %f, %f\n", position.x - offsetX, position.y - offsetY);
	textureAtlas->draw(renderer, MOVING_BULLET, position.x - offsetX, position.y - offsetY);
}