#ifndef CIVILIAN_SPRITE_H
#define CIVILIAN_SPRITE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "texture_atlas.h"
#include "spritesheet.h"
#include "sprite.h"
#include "action.h"

class CivilianSprite:public Sprite
{
	// pointer to player
	Sprite* playerSprite;
	// actions defining default sprite behavior, and current behavior
	//Action *defaultAction = new IdleAction(ACTION_LOOPING);
	//Action *defaultAction = new WanderAction(ACTION_LOOPING, 10, 1000, 500), *currAction;
	Action *defaultAction;
	
	public:
		CivilianSprite();
		CivilianSprite(float xCoord, float yCoord, Sprite* playerSprite, TextureAtlas* textureAtlas);
		void init(float xCoord, float yCoord, Sprite* playerSprite, TextureAtlas* textureAtlas); // todo: use initialization list (?)
		// finalizes movement and any other updates to the sprite's state
		void update(int ms);
		// draws sprite to the given surface/screen. Subtracting offsets from coordinates results in on-canvas coordinate to draw to
		void drawTo(SDL_Surface* screenSurface, int offsetX, int offsetY);
		
};

#endif