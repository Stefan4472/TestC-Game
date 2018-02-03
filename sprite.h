#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <vector>
#include "constants.h"
#include "spritesheet.h"
#include "item.h"
#include "healthbar.h"

// Sprite base class

class Sprite
{
	public: // TODO: MAKE SOME PRIVATE/PROTECTED
		Spritesheet idle_anim, mv_up_anim, mv_down_anim, mv_right_anim, mv_left_anim;
		// pointer to animation that's currently playing
		Spritesheet *current_anim = NULL;
		// offset of start of hitbox, from sprite's x and y (x + hitboxOffsetX = hitbox.x)
		int hitboxOffsetX, hitboxOffsetY;
		// offset of start of lineOfSight, from sprite's x and y
		int lineOfSightOffsetX, lineOfSightOffsetY;
		// healthbar, which may be drawn over the sprite
		SpriteHealthBar* healthbar = NULL;
		// sprite's movement speed, px per millisecond
		float moveSpeed = 0.25f;
		// distance sprite can see, and width of line of sight
		int sightDistance = 256, sightWidth = 96;
		
		// MAP_POSITION HITBOX? DRAW_POSITION?
	
		// virtual coordinates
		float x = -1, y = -1;
		// virtual coordinates at last frame
		float lastX = -1, lastY = -1;
		// pixels moved per ms in x and y
		float speedX = 0, speedY = 0;
		// hitpoints the sprite has at full health, and currently
		float fullHp = -1, currHp = -1;
		// area on map this sprite can be hit
		SDL_Rect hitbox { 0, 0, 0, 0 };
		// area on map this sprite can "see"
		SDL_Rect lineOfSight { 0, 0, 0, 0 };
		
		// direction currently moving in
		int movementDir = DIRECTION_NONE;
		// direction currently facing
		int facingDir = DIRECTION_DOWN;
		
		// item sprite is holding in-hand. Sprite is drawn to reflect it is holding the item
		Item* inHand = NULL;
		
		// called when the sprite's in-hand item changes. Listener function
		virtual void onInHandItemChanged(Item* item);
		// called when the sprite's health changes
		virtual void onHealthChanged();
		
		// get coordinates of sprite's right hand
		virtual SDL_Point getRightHandPosition() = 0;
		
		// sets coordinates to intended DIRECTION, given number of milliseconds since last frame
		void move(int ms);
		// sets speeds to make sprite walk in direction it is facing in
		void startWalking();
		// sets speeds to zero
		void stopMoving();
		// moves sprite to position it was at in previous frame
		void moveBack();
		// sets direction to given DIRECTION direction
		void setDir(int dir);
		
		// finalizes DIRECTION and any other updates to the sprite's state
		virtual void update(int ms);
		// adds given amount to sprite's currHp
		void addHealth(float amount);
		// subtracts given amount from sprite's currHp
		void loseHealth(float amount);
		// draws sprite to the given surface/screen. Subtracting offsets from coordinates results in on-canvas coordinate to draw to
		virtual void drawTo(SDL_Renderer* renderer, int offsetX, int offsetY);
		
};

#endif