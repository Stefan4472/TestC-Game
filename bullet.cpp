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

Bullet::Bullet(SDL_Rect position, SDL_Rect target, Sprite* attacker, Item* weapon) : Attack(position, 1, attacker, weapon)
{
	damage = 10;
	
	// calculate point bullet will travel to based on center of target plus some random amount
	int aim_x = (int) ((target.x + target.w) / 2 + (rand() % 2 ? 1 : -1) * (rand() % 16));
	int aim_y = (int) ((target.h + target.h) / 2 + (rand() % 2 ? 1 : -1) * (rand() % 16));
	
	// calculate angle bullet must travel to hit given point
	float travel_angle = atan((aim_y - position.y) * 1.0f / (aim_x - position.x));
	
	dx = cos(travel_angle) * 2.0f;
	dy = sin(travel_angle) * 2.0f;
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