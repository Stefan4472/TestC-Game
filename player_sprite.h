#ifndef SPRITE_H
#define SPRITE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "spritesheet.h"

enum MOVEMENT {
	MOVEMENT_NONE,
	MOVEMENT_UP,
	MOVEMENT_DOWN,
	MOVEMENT_LEFT,
	MOVEMENT_RIGHT	
};

class PlayerSprite
{
	float x, y, dx, dy;
	int movementDir = MOVEMENT_NONE; // todo: accomodate bidirectionality
	// default constructor: will be initialized in the PlayerSprite constructor
	Spritesheet idle_anim, mv_up_anim, mv_down_anim, mv_right_anim, mv_left_anim;
	// todo: hitbox

	public:
		PlayerSprite(float x, float y, 
					 SDL_Surface* idle_anim_sheet, 
					 SDL_Surface* mv_up_anim_sheet, 
					 SDL_Surface* mv_down_anim_sheet,
				 	 SDL_Surface* mv_left_anim_sheet,
				 	 SDL_Surface* mv_right_anim_sheet); // todo: use initialization list (?)
		void passTime(float elapsedSec);
		// draws sprite to the given surface/screen
		void drawTo(SDL_Surface* screenSurface);
		bool handleKeyEvent(SDL_Event e);
		~PlayerSprite();
		
};
#endif