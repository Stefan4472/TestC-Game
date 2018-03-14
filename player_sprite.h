#ifndef PLAYER_SPRITE_H
#define PLAYER_SPRITE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "texture_atlas.h"
#include "spritesheet.h"
#include "sprite.h"



// TODO: GOAL IS TO MAKE THIS ENTIRE CLASS REDUNDANT




// updating: handle input events in queue, call move(), check collisions, handle any collisions, update, draw
class PlayerSprite: public Sprite  
{
	// renderer 
	SDL_Renderer* renderer = NULL;
	
	public:
		PlayerSprite(float xCoord, float yCoord, TextureAtlas* textureAtlas, SDL_Renderer* renderer); // todo: use initialization list (?)
		// return coordinates of right hand
		SDL_Point getRightHandPosition();
};
#endif