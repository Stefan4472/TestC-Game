#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <vector>
#include "constants.h"
#include "animation_engine.h"

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
		// pointer to AnimationEngine
		AnimationEngine* animEngine = NULL;
		
		// registered listener
		SpriteListener* listener = NULL;
		
	public: // TODO: MAKE SOME PRIVATE/PROTECTED
		// create sprite of given type (see AnimationEngine)
		Sprite(int spriteType, AnimationEngine* animEngine);
		// type of sprite this is
		int spriteType = 0;
		// offset of start of hitbox, from sprite's x and y (x + hitboxOffsetX = hitbox.x)
		int hitboxOffsetX, hitboxOffsetY;
		// offset of start of lineOfSight, from sprite's x and y
		int lineOfSightOffsetX, lineOfSightOffsetY;
		// sprite's walking and running speeds, px per millisecond
		float walkSpeed = 0.25f, runSpeed = 0.40f;
		// distance sprite can see, and width of line of sight
		int sightDistance = 256, sightWidth = 96;
		
		// MAP_POSITION HITBOX? DRAW_POSITION?
	
		// animation player used by sprite TODO: MAKE PROTECTED, ADD DRAWTO()
		AnimationPlayer* animPlayer = NULL;
		
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
		
		// whether sprite is trying to aim in-hand item
		bool aiming = false;
		// coordinates of tile being aimed at. Only valid when aiming = true
		SDL_Rect aimRect = { 0, 0, 32, 32 };
		
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
		
		//void drawTo(SDL_Renderer* renderer, x, y);
		
};

#endif