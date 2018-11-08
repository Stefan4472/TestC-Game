#ifndef ATTACK_H
#define ATTACK_H

#include <SDL2/SDL.h>
#include "texture_atlas.h"
#include "sprite_action.h"
#include "direction.h"
class Sprite;

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
	protected:
		// number of ms this attack exists
		int duration = 0;
		// number of ms this attack has existed
		int elapsedTime = 0;

	public:
		Attack(SDL_Rect position, Sprite* attacker);
		// position attack currently covers in map
		SDL_Rect position;
		// whether attack is over, and can be deleted
		bool finished = false;
		// pointer to sprite that made the attack
		Sprite* attacker = NULL;
		// amount of damage the attack does in current state
		int damage = 0;
		// updates state of attack once given number of ms has passed
		virtual void update(int ms) = 0;
		// handles attack hitting a sprite. Default action is to set finished = true
		virtual void handleSpriteCollision();
		// handles attack hitting a map object. Default action is to set finished = true
		virtual void handleObjectCollision();
		// returns an action that would be done to the sprite on collision. Can be NULL
		virtual SpriteAction* getActionOnSprite(Sprite* sprite);
		// draws to screen
		virtual void drawToMap(SDL_Renderer* renderer, TextureAtlas* textureAtlas, float offsetX, float offsetY);
};
#endif
