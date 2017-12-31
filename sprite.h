#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include "spritesheet.h"

// Sprite base class

/*enum MOVEMENT {
	MOVEMENT_UP,
	MOVEMENT_UP_RIGHT,
	MOVEMENT_RIGHT, 
	MOVEMENT_DOWN_RIGHT,
	MOVEMENT_DOWN,
	MOVEMENT_DOWN_LEFT,
	MOVEMENT_LEFT,
	MOVEMENT_UP_LEFT,
	MOVEMENT_NONE
};*/

class Sprite
{
	protected:
		Spritesheet idle_anim, mv_up_anim, mv_down_anim, mv_right_anim, mv_left_anim;
		// pointer to animation that's currently playing
		Spritesheet *current_anim = NULL;
		// offset of start of hitbox, from sprite's x and y (x + hitboxOffsetX = hitbox.x)
		int hitboxOffsetX, hitboxOffsetY;
	
	public:
		// virtual coordinates
		float x, y;
		SDL_Rect hitbox;
		// sets coordinates to intended movement, given number of milliseconds since last frame
		virtual void move(int ms);
		// finalizes movement and any other updates to the sprite's state
		virtual void update(int ms);
		// draws sprite to the given surface/screen. Subtracting offsets from coordinates results in on-canvas coordinate to draw to
		virtual void drawTo(SDL_Surface* screenSurface, int offsetX, int offsetY);
		
};
#endif