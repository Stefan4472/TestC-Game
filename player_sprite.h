#ifndef PLAYER_SPRITE_H
#define PLAYER_SPRITE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "texture_atlas.h"
#include "spritesheet.h"
#include "action.h"
#include "sprite.h"
#include "item.h"

// updating: handle input events in queue, call move(), check collisions, handle any collisions, update, draw
class PlayerSprite: public Sprite
{
	// renderer 
	SDL_Renderer* renderer = NULL;
	
	// called when in-hand item changes: updates HUD
	void onInHandItemChanged(Item* newItem);
	
	public:
		PlayerSprite(float xCoord, float yCoord, TextureAtlas* textureAtlas, SDL_Renderer* renderer); // todo: use initialization list (?)
		// finalizes movement and any other updates to the sprite's state
		void update(int ms);
		// return coordinates of right hand
		SDL_Point getRightHandPosition();
		// draws sprite to the given surface/screen. Subtracting offsets from coordinates results in on-canvas coordinate to draw to
		void drawTo(SDL_Renderer* renderer, int offsetX, int offsetY);
		
		~PlayerSprite();
};
#endif