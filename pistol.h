#ifndef PISTOL_H
#define PISTOL_H

#include "texture_atlas.h"
#include "item.h"
#include "attack.h"
#include "bullet.h"
#include "action.h"
#include "knockback_action.h"

class Pistol : public Item
{
	// sprite using the pistol
	Sprite* actor = NULL;
	// direction gun is fired in
	int fireDirection = 0;
	// if gun was fired in this frame
	bool fired = false;
	// number of bullets in magazine
	int bulletsLoaded = 0;
	// max. number of bullets that can be loaded at one time
	const int MAG_SIZE = 10;
	// num milliseconds before gun can be fired again
	const int COOL_OFF = 500;	
	// num milliseconds since gun was last fired
	int msSinceShot = COOL_OFF;
	
	public:
		Pistol(TextureAtlas* textureAtlas, float x, float y);
		// adds to framesSinceShot
		void update(int ms);
		// attempts to fire the gun
		void use(Sprite* actor, SDL_Point handPos, int useDir);
		// attempts to load given item into the pistol
		bool reload(Item* item);
		// returns bullet fired in direction of shot
		Attack* getAttack();
		// returns knockback in opposite direction of shot
		Action* getAction();
};

#endif