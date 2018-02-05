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
	public:
		CivilianSprite(float x, float y, TextureAtlas* textureAtlas);		
};

#endif