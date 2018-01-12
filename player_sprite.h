#ifndef PLAYER_SPRITE_H
#define PLAYER_SPRITE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "texture_atlas.h"
#include "spritesheet.h"
#include "action.h"
#include "sprite.h"

// pixels moved in x/y per millisecond
const float PX_PER_MS = 0.25f;

// updating: handle input events in queue, call move(), check collisions, handle any collisions, update, draw
class PlayerSprite: public Sprite
{
	// coordinates at last frame--used for backtracking
	float lastX, lastY;
	// direction moving in currently
	int movementDir = DIRECTION_NONE; // todo: accomodate bidirectionality
	// default constructor: will be initialized in the PlayerSprite constructor
	Spritesheet idle_anim, mv_up_anim, mv_down_anim, mv_right_anim, mv_left_anim;
	// pointer to animatino that's currently playing
	Spritesheet *current_anim = NULL;
	// offset of start of hitbox, from sprite's x and y (x + hitboxOffsetX = hitbox.x)
	int hitboxOffsetX, hitboxOffsetY;
	
	public:
		PlayerSprite(float xCoord, float yCoord, TextureAtlas* textureAtlas); // todo: use initialization list (?)
		// sets coordinates to intended movement, given number of milliseconds since last frame
		void move(int ms);
		// moves sprite back to where it was the previous frame/move() 
		void moveBack();
		// finalizes movement and any other updates to the sprite's state
		void update(int ms);
		// return coordinates of right hand
		SDL_Point getRightHandPosition();
		// draws sprite to the given surface/screen. Subtracting offsets from coordinates results in on-canvas coordinate to draw to
		void drawTo(SDL_Renderer* renderer, int offsetX, int offsetY);
		// draws sprite's head's up display to the screen. Includes healthbar, in-hand item, etc.
		void drawHUD(SDL_Renderer* renderer);
		// given KeyEvent from user, sees whether it is relevant and consumes it. Returns true if it was consumed.
		bool handleKeyEvent(SDL_Event e);
		// whether key for interact has been pressed
		bool interactPressed = false;
		// whether the player has pressed key for interaction, and has been handled 
		bool interactHandled = false;
		~PlayerSprite();
		void changeDir(int newDir); // todo: clean up, currently the same as Sprite method
};
#endif