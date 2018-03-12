#include "pistol.h"

Pistol::Pistol() : Item(ITEM_PISTOL)
{
	ammunitionId = ITEM_BULLET;
}

void Pistol::update(int ms)
{
	msSinceShot += ms;	
}

void Pistol::use(Sprite* actor)
{
	printf("Pistol: actor direction is %d\n", actor->facingDir);
	if (bulletsLoaded && msSinceShot >= COOL_OFF)
	{
		SDL_Point hand_pos = actor->getRightHandPosition();
		SDL_Rect position = SDL_Rect { hand_pos.x, hand_pos.y, 32, 32 };
		//position.x = handPos.x;
		//position.y = handPos.y;
		//position.w = 32;
		//position.h = 32;
		
		printf("Sprite is using pistol\n");
		
		if (actor->aiming)
		{
			//SDL_Rect target = { actor->aimingX, actor->aimingY, 32, 32 };
			printf("Sprite is aiming at %d, %d\n", actor->aimRect.x, actor->aimRect.y); 
			lastFiredBullet = new Bullet(position, actor->aimRect, actor, this);	
		}
		else
		{
			lastFiredBullet = new Bullet(position, actor->facingDir, actor, this);
		}
		
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

bool Pistol::reload(Item* item)
{
	if (bulletsLoaded < MAG_SIZE && item->itemId == ammunitionId)
	{
		printf("Loading bullet into Pistol\n");
		bulletsLoaded++;
		return true;
	}
	return false;
}

Attack* Pistol::getAttack() 
{
	Attack* bullet = lastFiredBullet;
	lastFiredBullet = NULL;
	return bullet;
}

Action* Pistol::getAction() // TODO: CHECK IF PISTOL WAS FIRED? ORGANIZE DIRECTIONS SO WE CAN DO -(DIRECTION)?
{
	Action* recoil = lastRecoilAction;
	lastRecoilAction = NULL;
	return recoil;
}