#ifndef BULLET_ATTACK_H
#define BULLET_ATTACK_H

#include <SDL2/SDL.h>
#include "texture_atlas.h"
#include "attack.h"

//class Sprite;
//lass Item;

class Bullet : public Attack
{
	// speed bullet is travelling in x and y
	int dx = 0, dy = 0;
	
	public:
		Bullet(SDL_Rect position, int dir, Sprite* attacker, Item* weapon);
		void update(int ms);
		void drawToMap(SDL_Renderer* renderer, TextureAtlas* textureAtlas, float offsetX, float offsetY);
};

#endif