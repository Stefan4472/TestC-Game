#ifndef BULLET_ATTACK_H
#define BULLET_ATTACK_H

#include <SDL2/SDL.h>
#include <cmath>
#include "texture_atlas.h"
#include "attack.h"
class Gun;
#include "gun.h"
#include "sprite.h"

class FiredBullet : public Attack
{
	// maximum number of milliseconds this bullet can exist before requesting destruction
	const int MAX_DURATION = 2000;
	// overall bullet speed (different from speedX/speedY)
	const int BULLET_SPEED = 2.0f;
	
	// speed bullet is travelling in x and y
	float speedX = 0, speedY = 0;
	
	public:
		// create bullet fired by attacker using gun
		FiredBullet(Sprite* attacker, Gun* gun);
		// move bullet 
		void update(int ms);
		void drawToMap(SDL_Renderer* renderer, TextureAtlas* textureAtlas, float offsetX, float offsetY);
};

#endif