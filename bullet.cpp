#include "bullet.h"

Bullet::Bullet(SDL_Rect position, int dir, Sprite* attacker, Item* weapon) : Attack(position, dir, attacker, weapon)
{
	damage = 10;
	
	switch (dir)
	{
		case DIRECTION_RIGHT:
			dx = 2;
			break;
			
		case DIRECTION_LEFT:
			dx = -2;
			break;
			
		case DIRECTION_UP:
			dy = -2;
			break;
			
		case DIRECTION_DOWN:
			dy = 2;
			break;
	}	
}

void Bullet::update(int ms)
{
	elapsedTime += ms;
	
	// move bullet
	position.x += dx * ms;
	position.y += dy * ms;
	
	if (elapsedTime > MAX_DURATION)
	{
		finished = true;
		printf("Bullet Destroying itself because it has existed for too long\n");
	}
}

void Bullet::drawToMap(SDL_Renderer* renderer, TextureAtlas* textureAtlas, float offsetX, float offsetY)
{
	textureAtlas->draw(renderer, MOVING_BULLET, position.x - offsetX, position.y - offsetY);
}