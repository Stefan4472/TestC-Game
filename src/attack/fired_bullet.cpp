#include "fired_bullet.h"

FiredBullet::FiredBullet(Sprite* attacker, Gun* gun) : Attack(SDL_Rect { attacker->x, attacker->y, 32, 32 }/*attacker->getRightHandPosition()*/, attacker)
{
	switch (gun->ammunitionType)
	{
		case ItemType::PISTOL_AMMO:
			damage = 10;
			break;

		case ItemType::SHOTGUN_AMMO:
			damage = 40;
			break;

		case ItemType::RIFLE_AMMO:
			damage = 15;
			break;

		default:
			throw runtime_error("Invalid ItemType for a FiredBullet");
	}

	// sprite is aiming
	if (attacker->aiming)
	{
		SDL_Rect target = attacker->aimRect;
		//printf("Firing from %d, %d to %d, %d\n", position.x, position.y, target.x + target.w / 2, target.y + target.h / 2);

		// calculate point bullet will travel to based on center of target plus some small random amount NOTE: NOT A GREAT WAY TO DO THIS (PUNISHED CLOSE TARGETS MORE THAN FAR ONES)
		int aim_x = target.x + target.w / 2 + (rand() % 2 ? 1 : -1) * (rand() % 16);
		int aim_y = target.y + target.h / 2 + (rand() % 2 ? 1 : -1) * (rand() % 16);

		//printf("Randomized target to %d, %d\n", aim_x, aim_y);
		// calculate angle bullet must travel to hit given point
		float travel_angle = atan((aim_y - position.y) * 1.0f / (aim_x - position.x));
		//printf("Travel angle is %f\n", travel_angle);
		speedX = cos(travel_angle) * BULLET_SPEED;
		speedY = sin(travel_angle) * BULLET_SPEED;
		//printf("Speedx and y are %f, %f\n", speedX, speedY);
	}
	// not aiming: hip fire mechanic
	else
	{
		// hip fire has some inaccuracy! Find a small amount to adjust speed
		//float randomization = 0.0f;//(rand() % 2 ? 1 : -1) * (rand() % 16) / 80.0f;

		switch (attacker->facingDir)
		{
			case Direction::RIGHT:
				speedX = BULLET_SPEED;// - randomization;
				//speedY = randomization;
				break;

			case Direction::LEFT:
				speedX = -BULLET_SPEED;// - randomization;
				//speedY = randomization;
				break;

			case Direction::UP:
				speedY = -BULLET_SPEED;// - randomization;
				//speedY = randomization;
				break;

			case Direction::DOWN:
				speedY = BULLET_SPEED;// - randomization;
				//speedY = randomization;
				break;
		}
	}
}

void FiredBullet::update(int ms)
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

void FiredBullet::drawToMap(SDL_Renderer* renderer, TextureAtlas* textureAtlas,
	float offsetX, float offsetY)
{
	textureAtlas->drawImg(renderer, TextureId::MOVING_BULLET, position.x - offsetX, position.y - offsetY);
}
