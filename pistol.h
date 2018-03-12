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
	// max. number of bullets that can be loaded at one time
	const int MAG_SIZE = 10;
	// num milliseconds before gun can be fired again
	const int COOL_OFF = 500;	
	
	// bullet created when gun was last fired
	Bullet* lastFiredBullet = NULL;
	// recoil action created when gun was last fired
	Action* lastRecoilAction = NULL;
	// number of bullets in magazine
	int bulletsLoaded = 0;
	// num milliseconds since gun was last fired
	int msSinceShot = COOL_OFF;
	
	public:
		Pistol(y);
		// adds to framesSinceShot
		void update(int ms);
		// attempts to fire the gun
		void use(Sprite* actor);
		// attempts to load given item into the pistol
		bool reload(Item* item);
		// returns bullet fired in direction of shot
		Attack* getAttack();
		// returns knockback in opposite direction of shot
		Action* getAction();
};

#endif