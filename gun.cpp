#include "gun.h"

Gun::Gun(int itemId) : Item(itemId)
{
	switch (itemId)
	{
		case ITEM_PISTOL:		
			ammunitionId = ITEM_BULLET;
			magSize = 10;
			coolOff = 500;
			break;
			
		default:
			printf("ERROR: ItemID %d is not a gun! There may be unexpected behavior\n", itemId);
	}
	printf("Creating Gun with ID %d\n", itemId);
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

SpriteAction* Gun::getAction() // TODO: CHECK IF Gun WAS FIRED? ORGANIZE DIRECTIONS SO WE CAN DO -(DIRECTION)?
{
	SpriteAction* recoil = lastRecoilAction;
	lastRecoilAction = NULL;
	return recoil;
}