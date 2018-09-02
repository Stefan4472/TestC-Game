#ifndef GUN_H
#define GUN_H

#include <stdexcept>
#include "texture_atlas.h"
#include "sound_ids.h"
#include "item.h"
#include "attack.h"
class FiredBullet;
#include "fired_bullet.h"
#include "sprite_action.h"
#include "knockback_action.h"

/*
A gun is an Item that is used as a weapon and shoots damaging projectiles.
This class defines the base behavior each gun has. This includes a type of
bullet accepted (ItemType), amount of recoil, time between shots, magazine
size, and anything else the gun would need to know to operate correctly.
TODO: NOTE, CURRENT IMPLEMENTATION ASSIGNS DAMAGE BASED ON BULLET TYPE ONLY
*/
class Gun : public Item
{
	protected:
		// Item type used to load the gun NOTE: IMPLEMENTED IN ITEM CLASS
		//ItemType ammunitionId = ItemType::NONE;
		// max. number of bullets that can be loaded at one time
		int magSize;
		// num milliseconds before gun can be fired again
		int coolOff;
		// number of bullets in magazine
		int bulletsLoaded;
		// num milliseconds since gun was last fired
		int msSinceShot;
		Soun

		// bullet created when gun was last fired
		// consumed when getAttack() is called
		FiredBullet* lastFiredBullet = NULL;
		// recoil action created when gun was last fired. Goes in direction opposite
		// to where the gun was fired.
		// consumed when getAction() is called
		SpriteAction* lastRecoilAction = NULL;
		// sound created when gun was last fired or reloaded or TODO equipped
		Sound* lastSound = NULL;

	public:
		// creates a gun from the given ItemId, which must correspond to a gun type
		Gun(int itemId);
		// updates gun state, adding to msSinceShot (which allows the gun to cool off)
		void update(int ms);
		// attempts to load given item into the gun. Returns true if item is the
		// right type (equal to ammunitionId) and bulletsLoaded < magSize - 1
		bool load(Item* item);
		// attempts to fire the gun, which only works if there are bulletsLoaded
		// and the gun has cooled off since the last shot
		void use(Sprite* actor);
		// returns the most recent bullet fired, if any. Consumes lastFiredBullet.
		Attack* getAttack();
		// returns knockback in opposite direction of shot, if any. Consumes
		// lastRecoilAction
		SpriteAction* getAction();
		// adds lastSound to the list if it exists, and resets
		void getAndClearSounds(vector<Sounds> sounds);
};

#endif
