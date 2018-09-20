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
		// max. number of bullets that can be loaded at one time
		int magSize;
		// number of bullets in magazine
		int bulletsLoaded;
		// num milliseconds before gun can be fired again
		int coolOff;
		// num milliseconds since gun was last fired
		int msSinceShot;
		// offsets added to sprite's hand position to get coordinates where bullet
		// is shot. TODO: MAKE ARRAY?
		int muzzleOffsetX, muzzleOffsetY;
		// damage this bullet does when it hits a player/NPC/object
		int bulletDamage;
		// time it takes to reload TODO?
		int reloadTime;
		// number of pixels firing the gun sends the shooter back TODO: MAKE MORE SOPHISTICATED?
		int recoilAmountPx;
		// the type of sound this gun makes when shot
		SoundType shotSoundType;
		// the type of sound this gun makes when reloaded
		SoundType reloadSoundType;
		// the type of sound this gun makes when equipped TODO
		SoundType equipSoundType;

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
		// type of ammunition this gun accepts
		ItemType ammunitionType;
		// creates a gun from the given ItemId, which must correspond to a gun type
		Gun(ItemType itemType);
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
		void getAndClearSounds(vector<Sound*> sounds);
};

#endif
