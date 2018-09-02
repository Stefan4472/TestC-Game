#include "gun.h"

Gun::Gun(int itemId) : Item(itemId)
{
	printf("Creating gun with id %d (%s)\n", itemId, name.c_str());
	bulletsLoaded = 0;

	switch (itemId)
	{
		case ItemType::PISTOL:
			magSize = 8;
			coolOff = 300;
			muzzleOffsetX = 12;
			muzzleOffsetY = -5;
			bulletDamage = 10;
			shotSoundType = SoundType::PISTOL_SHOT;
			recoilAmountPx = 10;
			break;

		case ItemType::SHOTGUN:
			magSize = 2;
			coolOff = 500;
			muzzleOffsetX = 24;
			muzzleOffsetY = -5;
			bulletDamage = 40;
			shotSoundType = SoundType::SHOTGUN_SAWED_OFF_SHOT;
			recoilAmountPx = 40;
			break;

		case ItemType::TOMMYGUN:
			magSize = 24;
			coolOff = 30;
			muzzleOffsetX = 24;
			muzzleOffsetY = -5;
			bulletDamage = 15;
			shotSoundType = SoundType::RIFLE_SHOT;
			recoilAmountPx = 8;
			break;

		default:
			raise runtime_error("Invalid ItemId, does not correspond to a gun");
	}

	// allow gun to be fired immediately
	msSinceShot = coolOff;
}

void Gun::update(int ms)
{
	msSinceShot += ms;
}

void Gun::use(Sprite* actor)
{
	printf("Gun: actor direction is %d\n", actor->facingDir);
	if (bulletsLoaded && msSinceShot >= coolOff)
	{
		SDL_Point hand_pos = actor->getRightHandPosition();
		SDL_Rect position = SDL_Rect { hand_pos.x, hand_pos.y, 32, 32 };
		//position.x = handPos.x;
		//position.y = handPos.y;
		//position.w = 32;
		//position.h = 32;

// TODO: ADD THE GIVEN PARAMETERS
		lastSound = new Sound(shotSoundId, hand_pos.x, hand_pos.y, shotSoundRadius, actor);

		printf("Sprite is using Gun\n");

		lastFiredBullet = new FiredBullet(actor, this);

		switch (actor->facingDir)
		{
			case DIRECTION_RIGHT:
				lastRecoilAction = new KnockbackAction(DIRECTION_LEFT);
				break;

			case DIRECTION_UP:
				lastRecoilAction = new KnockbackAction(DIRECTION_DOWN);
				break;

			case DIRECTION_LEFT:
				lastRecoilAction = new KnockbackAction(DIRECTION_RIGHT);
				break;

			case DIRECTION_DOWN:
				lastRecoilAction = new KnockbackAction(DIRECTION_UP);
				break;
		}

		bulletsLoaded--;
	}
	else
	{
		printf("No bullets loaded!\n");
	}
}

bool Gun::load(Item* item)
{
	if (bulletsLoaded < magSize && item->itemId == ammunitionId)
	{
		printf("Loading bullet into Gun\n");
		bulletsLoaded++;
		return true;
	}
	return false;
}

Attack* Gun::getAttack()
{
	Attack* bullet = lastFiredBullet;
	lastFiredBullet = NULL;
	return bullet;
}

SpriteAction* Gun::getAction()
{
	SpriteAction* recoil = lastRecoilAction;
	lastRecoilAction = NULL;
	return recoil;
}

void Gun::getAndClearSounds(vector<Sounds> sounds)
{
	if (lastSound)
	{
		sounds.push_back(lastSound);
		lastSound = NULL;
	}
}
