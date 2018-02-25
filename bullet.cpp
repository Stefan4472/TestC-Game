#include "bullet.h"

Bullet::Bullet(SDL_Rect position, int dir, Sprite* attacker, Item* weapon) : Attack(position, dir, attacker, weapon)
{
	damage = 10;
	
	switch (dir)
	{
		case DIRECTION_RIGHT:
			speedX = 2;
			break;
			
		case DIRECTION_LEFT:
			speedX = -2;
			break;
			
		case DIRECTION_UP:
			speedY = -2;
			break;
			
		case DIRECTION_DOWN:
			speedY = 2;
			break;
	}	
}

Bullet::Bullet(SDL_Rect position, SDL_Rect target, Sprite* attacker, Item* weapon) : Attack(position, 1, attacker, weapon)
{
	damage = 10;
	
	printf("Firing from %d, %d to %d, %d\n", position.x, position.y, target.x + target.w / 2, target.y + target.h / 2);
	// calculate point bullet will travel to based on center of target plus some random amount
	int aim_x = target.x + target.w / 2;// + (rand() % 2 ? 1 : -1) * (rand() % 16);
	int aim_y = target.y + target.h / 2;// + (rand() % 2 ? 1 : -1) * (rand() % 16);
	
	printf("Randomized target to %d, %d\n", aim_x, aim_y);
	// calculate angle bullet must travel to hit given point
	float travel_angle = atan((aim_y - position.y) * 1.0f / (aim_x - position.x));
	printf("Travel angle is %f\n", travel_angle);
	speedX = cos(travel_angle) * 2.0f;
	speedY = sin(travel_angle) * 2.0f;
	printf("Speedx and y are %f, %f\n", speedX, speedY);
}

void Bullet::update(int ms)
{
	elapsedTime += ms;
	
	// move bullet
	position.x += speedX * ms;
	position.y += speedY * ms;
	
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