#ifndef BULLET_ATTACK_H
#define BULLET_ATTACK_H

#include <SDL2/SDL.h>
#include <cmath>
#include "texture_atlas.h"
#include "attack.h"

class Bullet : public Attack
{
	// speed bullet is travelling in x and y
	int dx = 0, dy = 0;
	// number of ms bullet has existed
	int elapsedTime = 0;
	// maximum number of milliseconds this bullet can exist before requesting destruction
	const int MAX_DURATION = 2000;
	
	public:
		// "hip fire", given position and direction
		Bullet(SDL_Rect position, int dir, Sprite* attacker, Item* weapon);
		// aimed fire, from point gun is at to tile aimed at
		Bullet(SDL_Rect position, SDL_Rect target, Sprite* attacker, Item* weapon);
		// move bullet 
		void update(int ms);
		void drawToMap(SDL_Renderer* renderer, TextureAtlas* textureAtlas, float offsetX, float offsetY);
};

#endif