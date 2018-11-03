#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <vector>
#include <stdexcept>
#include "sprite_listener.h"
#include "direction.h"
#include "move_state.h"
#include "sprite_type.h"

/*
Sprite base class. This is a kind of "low-level" class, it's meant to be
manipulated and provide basic logic but doesn't know the actions it's doing.
*/
class Sprite  // TODO: IMPLEMENT MAPOBJECT FOR DRAWING. KNOCKBACK(POWER) METHOD, WEIGHT ATTRIBUTE, ARMOR ATTRIBUTE
{
	protected:
		// registered listener for state-change callbacks
		SpriteListener* listener = NULL;

	public: // TODO: MAKE SOME PRIVATE/PROTECTED. MAKE COORDINATES DOUBLE
		// create sprite of given type at given game coordinates
		Sprite(SpriteType spriteType, float x, float y, SpriteListener* listener);
		// type of sprite this is
		SpriteType spriteType = SpriteType::NONE;
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

		// game coordinates of sprite top-left
		float x, y;
		// virtual coordinates at last frame TODO: WHAT IF SPRITE CAN'T BE PLACED IN FIRST FRAME OF EXISTENCE?
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
		Direction facingDir = DIRECTION::NONE;
		MoveState moveState;

		// // whether sprite is trying to aim in-hand item
		// bool aiming = false;
		// // coordinates of tile being aimed at. Only valid when aiming = true
		// SDL_Rect aimRect = { 0, 0, 32, 32 };

		// get coordinates of sprite's right hand
		virtual SDL_Point getRightHandPosition();

		// TODO: COMMENTING
		void move(int ms);
		void startWalking();
		void startRunning();
		void stopMoving();
		void moveBack();
		void setDir(Direction dir);

		// finalizes DIRECTION and any other updates to the sprite's state
		virtual void update(int ms);
		// adds given amount to sprite's currHp
		void addHealth(float amount);
		// subtracts given amount from sprite's currHp
		void loseHealth(float amount);
};

#endif
