#ifndef CIVILIAN_SPRITE_H
#define CIVILIAN_SPRITE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "spritesheet.h"
#include "sprite.h"

class CivilianSprite
{
	// default constructor: will be initialized in the PlayerSprite constructor
	Spritesheet idle_anim, mv_up_anim, mv_down_anim, mv_right_anim, mv_left_anim;
	// pointer to animatino that's currently playing
	Spritesheet *current_anim = NULL;
	// offset of start of hitbox, from sprite's x and y (x + hitboxOffsetX = hitbox.x)
	int hitboxOffsetX, hitboxOffsetY;
	
	public:
		// virtual coordinates
		float x, y;
		SDL_Rect hitbox;
		void init(float xCoord, float yCoord,
					 SDL_Surface* idle_anim_sheet, 
					 SDL_Surface* mv_up_anim_sheet, 
					 SDL_Surface* mv_down_anim_sheet,
				 	 SDL_Surface* mv_left_anim_sheet,
				 	 SDL_Surface* mv_right_anim_sheet); // todo: use initialization list (?)
		// sets coordinates to intended movement, given number of milliseconds since last frame
		void move(int ms);
		// finalizes movement and any other updates to the sprite's state
		void update(int ms);
		// draws sprite to the given surface/screen. Subtracting offsets from coordinates results in on-canvas coordinate to draw to
		void drawTo(SDL_Surface* screenSurface, int offsetX, int offsetY);
		// todo: interact
		
};

#endif