#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <vector>
#include "constants.h"
#include "spritesheet.h"
#include "item.h"
#include "inventory.h"
#include "trigger.h"
#include "attack.h"
#include "sound.h"
#include "healthbar.h"

class Action;

// Sprite base class

class Sprite
{
	protected:
		Spritesheet idle_anim, mv_up_anim, mv_down_anim, mv_right_anim, mv_left_anim;
		// pointer to animation that's currently playing
		Spritesheet *current_anim = NULL;
		// offset of start of hitbox, from sprite's x and y (x + hitboxOffsetX = hitbox.x)
		int hitboxOffsetX, hitboxOffsetY;
		// offset of start of lineOfSight, from sprite's x and y
		int lineOfSightOffsetX, lineOfSightOffsetY;
		// default DIRECTION speed
		float speedPerMs = 0;
		// current action controlling the sprite
		Action* currAction = NULL;
		// healthbar, which may be drawn over the sprite
		SpriteHealthBar* healthbar;
		// list of buffs currently affecting player
		std::vector<Action*> buffs;
		// sprite's movement speed, px per millisecond
		float moveSpeed = 0.25f;
		// distance sprite can see, and width of line of sight
		int sightDistance = 256, sightWidth = 96;
		
		// TODO: LIST (or hashmap) OF FRIENDLY SPRITES, LIST OF ENEMY SPRITES. LINE OF SIGHT HITBOX. MAP_POSITION HITBOX?
	
	public:
		// virtual coordinates
		float x = -1, y = -1;
		// virtual coordinates at last frame
		float lastX = -1, lastY = -1;
		// hitpoints the sprite has at full health, and currently
		float fullHp = -1, currHp = -1;
		// area on map this sprite can be hit
		SDL_Rect hitbox { 0, 0, 0, 0 };
		// area on map this sprite can "see"
		SDL_Rect lineOfSight { 0, 0, 0, 0 };
		
		// sprite's inventory
		Inventory* inventory = NULL; 
		// list of Items sprite wants to drop. Meant to be picked up by the Map/Gamedriver
		std::vector<Item*> drops;
		// list of Attacks sprite wants to carry out. Meant to be picked up by the Map/Gamedriver
		// a sprite may have multiple attacks progressing, e.g. if several bullets have been fired
		std::vector<Attack*> attacks;
		// list of SoundIds the sprite has requested. Meant to be picked up by the Map/Gamedriver
		std::vector<int> sounds;
		
		// direction currently moving in
		int movementDir = DIRECTION_NONE;
		// direction currently facing
		int facingDir = DIRECTION_DOWN;
		
		// called when the sprite's in-hand item changes. Listener function
		virtual void onInHandChanged(int id);
		// called when the sprite's health changes
		virtual void onHealthChanged();
		
		// get coordinates of sprite's right hand
		virtual SDL_Point getRightHandPosition() = 0;
		
		// sets coordinates to intended DIRECTION, given number of milliseconds since last frame
		void move(int ms);
		// moves sprite to position it was at in previous frame
		void moveBack();
		// changes to given DIRECTION direction
		void changeDir(int newDir);
		// handles a trigger (event a sprite is made aware of)
		virtual void handleTrigger(Trigger* trigger);
		
		// responds to sprite being attacked
		virtual void handleAttacked(Attack* attack) = 0;
		// handles sprite hearing a sound 
		virtual void handleSoundHeard(Sound* sound) = 0;
		// handles sprite seeing another sprite 
		virtual void handleSpriteSeen(Sprite* sprite) = 0;
		
		// finalizes DIRECTION and any other updates to the sprite's state
		virtual void update(int ms);
		// adds given amount to sprite's currHp
		void addHealth(float amount);
		// subtracts given amount from sprite's currHp
		void loseHealth(float amount);
		// draws sprite to the given surface/screen. Subtracting offsets from coordinates results in on-canvas coordinate to draw to
		virtual void drawTo(SDL_Renderer* renderer, int offsetX, int offsetY) = 0;
		
};

#endif