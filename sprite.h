#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include "spritesheet.h"
#include "item.h"
#include "inventory.h"

// Sprite base class

enum MOVEMENT {
	MOVEMENT_UP,
	//MOVEMENT_UP_RIGHT,
	MOVEMENT_RIGHT, 
	//MOVEMENT_DOWN_RIGHT,
	MOVEMENT_DOWN,
	//MOVEMENT_DOWN_LEFT,
	MOVEMENT_LEFT,
	//MOVEMENT_UP_LEFT,
	MOVEMENT_NONE
};

class Sprite
{
	protected:
		Spritesheet idle_anim, mv_up_anim, mv_down_anim, mv_right_anim, mv_left_anim;
		// pointer to animation that's currently playing
		Spritesheet *current_anim = NULL;
		// offset of start of hitbox, from sprite's x and y (x + hitboxOffsetX = hitbox.x)
		int hitboxOffsetX, hitboxOffsetY;
		// default movement speed
		float speedPerMs = 0;
	
	public:
		// virtual coordinates
		float x, y;
		// area on map this sprite can be hit
		SDL_Rect hitbox;
		// objects sprite is carrying
		Inventory inventory;
		// direction currently moving in
		int movementDir = MOVEMENT_NONE;
		// sets coordinates to intended movement, given number of milliseconds since last frame
		virtual void move(int ms);
		// changes to given movement direction
		virtual void changeDir(int newDir);
		// finalizes movement and any other updates to the sprite's state
		virtual void update(int ms);
		// draws sprite to the given surface/screen. Subtracting offsets from coordinates results in on-canvas coordinate to draw to
		virtual void drawTo(SDL_Surface* screenSurface, int offsetX, int offsetY)=0;
		
};

#endif