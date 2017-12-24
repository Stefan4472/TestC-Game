#ifndef SPRITE_H
#define SPRITE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "spritesheet.h"

enum MOVEMENT {
	MOVEMENT_UP,
	MOVEMENT_UP_RIGHT,
	MOVEMENT_RIGHT, 
	MOVEMENT_DOWN_RIGHT,
	MOVEMENT_DOWN,
	MOVEMENT_DOWN_LEFT,
	MOVEMENT_LEFT,
	MOVEMENT_UP_LEFT,
	MOVEMENT_NONE
};

// updating: handle input events in queue, call move(), check collisions, handle any collisions, update, draw
class PlayerSprite
{
	float x, y, dx, dy;
	float SPEED_CAP = 0.6f;
	int movementDir = MOVEMENT_NONE; // todo: accomodate bidirectionality
	// default constructor: will be initialized in the PlayerSprite constructor
	Spritesheet idle_anim, mv_up_anim, mv_down_anim, mv_right_anim, mv_left_anim;
	Spritesheet *current_anim = NULL;
	// todo: hitbox

	public:
		PlayerSprite(float xCoord, float yCoord,
					 SDL_Surface* idle_anim_sheet, 
					 SDL_Surface* mv_up_anim_sheet, 
					 SDL_Surface* mv_down_anim_sheet,
				 	 SDL_Surface* mv_left_anim_sheet,
				 	 SDL_Surface* mv_right_anim_sheet); // todo: use initialization list (?)
		// sets coordinates to intended movement, given number of milliseconds since last frame
		void move(int ms);
		// finalizes movement and any other updates to the sprite's state
		void update(int ms);
		// draws sprite to the given surface/screen
		void drawTo(SDL_Surface* screenSurface);
		bool handleKeyEvent(SDL_Event e);
		~PlayerSprite();
		
	private:
		// changes movement direction todo: given the Movement constant that has been added/removed from input.
		// positive input = player intends to go in that direction. negative input = player released key going in direction
		void changeDir(int newDir);
};
#endif