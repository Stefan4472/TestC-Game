#include "gun.h"

Gun::Gun(ItemType itemType) : Item(itemType)
{
	bulletsLoaded = 0;

	switch (itemType)
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
			throw runtime_error("Invalid ItemId, does not correspond to a gun");
	}

	// allow gun to be fired immediately
	msSinceShot = coolOff;
	// get the type of ammunition this gun takes
	ammunitionType = Item::getAmmunitionType(itemType);
}

void Gun::update(int ms)
{
	msSinceShot += ms;
}

void Gun::use(Sprite* actor)
{
	printf("Gun: actor direction is %d\n", static_cast<int>(actor->facingDir));
	if (bulletsLoaded && msSinceShot >= coolOff)
	{
		SDL_Point hand_pos = actor->getRightHandPosition();
		SDL_Rect position = SDL_Rect { hand_pos.x, hand_pos.y, 32, 32 };
		//position.x = handPos.x;
		//position.y = handPos.y;
		//position.w = 32;
		//position.h = 32;

// TODO: ADD THE GIVEN PARAMETERS
		lastSound = new Sound(shotSoundType, hand_pos.x, hand_pos.y, actor);

		printf("Sprite is using Gun\n");

		lastFiredBullet = new FiredBullet(actor, this);

		switch (actor->facingDir)
		{
			case Direction::RIGHT:
				lastRecoilAction = new KnockbackAction(Direction::LEFT);
				break;

			case Direction::UP:
				lastRecoilAction = new KnockbackAction(Direction::DOWN);
				break;

			case Direction::LEFT:
				lastRecoilAction = new KnockbackAction(Direction::RIGHT);
				break;

			case Direction::DOWN:
				lastRecoilAction = new KnockbackAction(Direction::UP);
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
	if (bulletsLoaded < magSize && item->itemType == ammunitionType)
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

void Gun::getAndClearSounds(vector<Sound*> sounds)
{
	if (lastSound)
	{
		sounds.push_back(lastSound);
		lastSound = NULL;
	}
}
