#ifndef GUN_H
#define GUN_H

#include "texture_atlas.h"
#include "item.h"
#include "attack.h"
#include "bullet.h"
#include "action.h"
#include "knockback_action.h"

// A gun is an item that is used as a weapon and shoots damaging projectiles.
// This class defines the base behavior each gun has. This includes a type of
// bullet accepted (bulletType), amount of recoil, time between shots, magazine
// size, range, and anything else.

class Gun : public Item
{
	protected:
		// max. number of bullets that can be loaded at one time
		int magSize = 10;
		// num milliseconds before gun can be fired again
		int coolOff = 500;	
	
		// bullet created when gun was last fired
		Bullet* lastFiredBullet = NULL;
		// recoil action created when gun was last fired
		Action* lastRecoilAction = NULL;
		// number of bullets in magazine
		int bulletsLoaded = 0;
		// num milliseconds since gun was last fired
		int msSinceShot = coolOff;
	
	public:
		// creates a gun from the given ItemId. Must be a valid id
		Gun(int itemId);
		// adds to framesSinceShot
		void update(int ms);
		// attempts to fire the gun
		void use(Sprite* actor);
		// attempts to load given item into the pistol
		bool load(Item* item);
		// returns bullet fired in direction of shot
		Attack* getAttack();
		// returns knockback in opposite direction of shot
		Action* getAction();
};

#endif