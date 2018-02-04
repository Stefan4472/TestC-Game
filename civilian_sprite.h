#ifndef CIVILIAN_SPRITE_H
#define CIVILIAN_SPRITE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "texture_atlas.h"
#include "sound_atlas.h"
#include "spritesheet.h"
#include "sprite.h"
#include "action.h"
#include "action_set.h"

class CivilianSprite : public Sprite
{
	// pointer to player
	Sprite* playerSprite;
	
	public:
		CivilianSprite(float xCoord, float yCoord, Sprite* playerSprite, TextureAtlas* textureAtlas);		
};

#endif