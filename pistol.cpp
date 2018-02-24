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
	if (bulletsLoaded)
	{
		this->actor = actor;
		fireDirection = useDir;
		fired = true;
		position.x = handPos.x;
		position.y = handPos.y;
		position.w = 32;
		position.h = 32;
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
	if (fired && msSinceShot >= COOL_OFF)
	{
		msSinceShot = 0;
		fired = false;
		//SDL_Rect position, int dir, Sprite* attacker, Item* weapon
		return new Bullet(position, fireDirection, actor, this);
	}
	fired = false;
}

Action* Pistol::getAction() // TODO: CHECK IF PISTOL WAS FIRED? ORGANIZE DIRECTIONS SO WE CAN DO -(DIRECTION)?
{
	switch (fireDirection)
	{
		case DIRECTION_RIGHT:
			return new KnockbackAction(DIRECTION_LEFT);
			
		case DIRECTION_UP:
			return new KnockbackAction(DIRECTION_DOWN);
			
		case DIRECTION_LEFT:
			return new KnockbackAction(DIRECTION_RIGHT);
			
		case DIRECTION_DOWN:
			return new KnockbackAction(DIRECTION_UP);
	}
	return NULL;
}