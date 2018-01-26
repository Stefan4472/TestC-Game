#ifndef ATTACK_H
#define ATTACK_H

#include <SDL2/SDL.h>
#include "constants.h"
#include "texture_atlas.h"

class Sprite;
class Item;

// An Attack is created by a Sprite. It has a direction it is exerted in, and a
// position where it occurs on the map, defined by a rect. It also has a pointer
// to the initiating Sprite, and a pointer to the weapon used.

// Attacks can change over time, for example a bullet moving, or an explosion. 
// This is implemented via the update() method, which passes the number of 
// milliseconds since the last frame the attack was used in.

// An attack can sometimes also be drawn to the map (e.g. a Bullet). Such attacks
// can override the drawTo method.
class Attack
{	
	private:
		// number of ms this attack exists
		int duration = 0;
		// number of ms this attack has existed
		int elapsedTime = 0;
		
	public:
		Attack(SDL_Rect position, int dir, Sprite* attacker, Item* weapon);
		// positino attack covers in map
		SDL_Rect position;
		// direction attack is directed in
		int dir = 0;
		// whether attack is over, and can be deleted
		bool finished = false;
		// pointer to sprite that made the attack
		Sprite* attacker = NULL;
		// item used in the attack
		Item* weapon = NULL;
		// amount of damage the attack does in current state
		int damage = 0;
		// updates state of attack once given number of ms has passed
		virtual void update(int ms) = 0;
		// draws to screen
		virtual void drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas, float offsetX, float offsetY);
};

class SwordSwing : public Attack
{
	public:
		SwordSwing(SDL_Rect position, int dir, Sprite* attacker, Item* weapon);
		void update(int ms);
};

class Bullet : public Attack
{
	// speed bullet is travelling in x and y
	int dx = 0, dy = 0;
	
	public:
		Bullet(SDL_Rect position, int dir, Sprite* attacker, Item* weapon);
		void update(int ms);
		void drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas, float offsetX, float offsetY);
};
#endif