#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <vector>
#include "constants.h"
#include "spritesheet.h"
#include "item.h"

// Listener interface for receiving sprite callbacks
class SpriteListener
{
	public:
		virtual void onSpriteHealthChanged(int amount, int currHealth) = 0;
};

// Sprite base class

class Sprite
{
	protected:
		// spritesheets for idling (not moving) while facing different directions
		Spritesheet *idle_right_anim = NULL, *idle_left_anim = NULL, *idle_up_anim = NULL, *idle_down_anim = NULL;
		// spritesheets for walking in different directions
		Spritesheet *walk_up_anim = NULL, *walk_down_anim = NULL, *walk_right_anim = NULL, *walk_left_anim = NULL;
		// spritesheets for running in different directions
		Spritesheet *run_up_anim = NULL, *run_down_anim = NULL, *run_right_anim = NULL, *run_left_anim = NULL;
		// array of idle spritesheets, indexed by direction
		Spritesheet* idle_anims[5] = { NULL, idle_up_anim, idle_down_anim, idle_right_anim, idle_left_anim };
		// array of walk spritesheets, indexed by direction
		Spritesheet* walk_anims[5] = { NULL, walk_up_anim, walk_down_anim, walk_right_anim, walk_left_anim };
		// array of run spritesheets, indexed by direction
		Spritesheet* run_anims[5] = { NULL, run_up_anim, run_down_anim, run_right_anim, run_left_anim };
		
		// pointer to animation that's currently playing
		Spritesheet *current_anim = NULL;
		// pointer to current action animations
		Spritesheet** current_anim_array = idle_anims;
		
		// registered listener
		SpriteListener* listener = NULL;
		
	public: // TODO: MAKE SOME PRIVATE/PROTECTED
		// initializes arrays of Spritesheets
		void init();
		// offset of start of hitbox, from sprite's x and y (x + hitboxOffsetX = hitbox.x)
		int hitboxOffsetX, hitboxOffsetY;
		// offset of start of lineOfSight, from sprite's x and y
		int lineOfSightOffsetX, lineOfSightOffsetY;
		// sprite's walking and running speeds, px per millisecond
		float walkSpeed = 0.25f, runSpeed = 0.40f;
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
		
		// sets sprite's listener
		void setListener(SpriteListener* listener);
		
		// whether sprite has hit 0 hp and is dead
		bool dead = false;
		// whether sprite should be deleted and removed from game
		bool destroy = false;
		
		// direction currently facing
		int facingDir = DIRECTION_DOWN;
		
		// item sprite is holding in-hand. Sprite is drawn to reflect it is holding the item
		Item* inHand = NULL;
		
		// called when the sprite's in-hand item changes. Listener function
		virtual void onInHandItemChanged(Item* item);
		
		// get coordinates of sprite's right hand
		virtual SDL_Point getRightHandPosition();
		
		// sets coordinates to intended DIRECTION, given number of milliseconds since last frame
		void move(int ms);
		// sets speeds and animation to make sprite walk in direction it is facing in
		void startWalking();
		// sets speeds and animation to make sprite run in direction it is facing in
		void startRunning();
		// sets speeds to zero and animation to idle in current facingDir
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