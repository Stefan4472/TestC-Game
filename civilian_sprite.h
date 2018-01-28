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
	// number of frames that healthbar should be shown (0 = don't show)
	int numHealthbarFrames = 0;
	
	public:
		CivilianSprite(float xCoord, float yCoord, Sprite* playerSprite, TextureAtlas* textureAtlas);
		// finalizes movement and any other updates to the sprite's state
		void update(int ms);
		// return coordinates of right hand
		SDL_Point getRightHandPosition();
		
		// shows the healthbar for a given number of frames
		void showHealthbar();
		// draws sprite to the given surface/screen. Subtracting offsets from coordinates results in on-canvas coordinate to draw to
		void drawTo(SDL_Renderer* renderer, int offsetX, int offsetY);
		
};

#endif