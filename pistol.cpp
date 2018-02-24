#include "pistol.h"

Pistol::Pistol(TextureAtlas* textureAtlas, float x, float y) : Item(textureAtlas, ITEM_PISTOL, x, y)
{
	ammunitionId = ITEM_BULLET;
}

void Pistol::update(int ms)
{
	msSinceShot += ms;	
}

void Pistol::use(Sprite* actor, SDL_Point handPos, int useDir)
{
	printf("Pistol: actor direction is %d\n", actor->facingDir);
	if (bulletsLoaded && msSinceShot >= COOL_OFF)
	{
		position.x = handPos.x;
		position.y = handPos.y;
		position.w = 32;
		position.h = 32;
		lastFiredBullet = new Bullet(position, actor->facingDir, actor, this);
		
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
	if (bulletsLoaded < MAG_SIZE && item->itemType == ammunitionId)
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