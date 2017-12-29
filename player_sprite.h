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

// pixels moved in x/y per millisecond
const float PX_PER_MS = 0.25f;

// updating: handle input events in queue, call move(), check collisions, handle any collisions, update, draw
class PlayerSprite
{
	// coordinates at last frame--used for backtracking
	float lastX, lastY;
	// direction moving in currently
	int movementDir = MOVEMENT_NONE; // todo: accomodate bidirectionality
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
		PlayerSprite(float xCoord, float yCoord,
					 SDL_Surface* idle_anim_sheet, 
					 SDL_Surface* mv_up_anim_sheet, 
					 SDL_Surface* mv_down_anim_sheet,
				 	 SDL_Surface* mv_left_anim_sheet,
				 	 SDL_Surface* mv_right_anim_sheet); // todo: use initialization list (?)
		// sets coordinates to intended movement, given number of milliseconds since last frame
		void move(int ms);
		// moves sprite back to where it was the previous frame/move() 
		void moveBack();
		// finalizes movement and any other updates to the sprite's state
		void update(int ms);
		// draws sprite to the given surface/screen. Subtracting offsets from coordinates results in on-canvas coordinate to draw to
		void drawTo(SDL_Surface* screenSurface, int offsetX, int offsetY);
		// given KeyEvent from user, sees whether it is relevant and consumes it. Returns true if it was consumed.
		bool handleKeyEvent(SDL_Event e);
		// return virtual x- and y-coordinates of point where the player's feet are
		float getPosX(); // TODO: Point class, one function call for x and y
		float getPosY();
		~PlayerSprite();
		
	private:
		// changes movement direction todo: given the Movement constant that has been added/removed from input.
		// positive input = player intends to go in that direction. negative input = player released key going in direction
		void changeDir(int newDir);
};
#endif