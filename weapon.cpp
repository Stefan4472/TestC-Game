#include "weapon.h"

Sword::Sword(TextureAtlas* textureAtlas, float x, float y) : Item(textureAtlas, ITEM_SWORD, x, y)
{
	damage = 10;
}

void Sword::use(Sprite* actor, SDL_Point handPos, int useDir)
{
	this->actor = actor;
	swingDirection = useDir;
	// set position pased on handPosition and direction
	switch (useDir)
	{
		case DIRECTION_RIGHT:		 // todo: this will require tweaking
			position.x = handPos.x;
			position.y = handPos.y - 16;
			break;
			
		case DIRECTION_LEFT:
			position.x = handPos.x - 32;
			position.y = handPos.y - 16;
			break;
			
		case DIRECTION_UP:
			position.x = handPos.x - 16;
			position.y = handPos.y - 32;
			break;
			
		case DIRECTION_DOWN:
			position.x = handPos.x - 16;
			position.y = handPos.y;
			break;
	}
}

Attack* Sword::getAttack()
{
	return new SwordSwing(position, swingDirection, actor, this);
}

Pistol::Pistol(TextureAtlas* textureAtlas, float x, float y) : Item(textureAtlas, ITEM_PISTOL, x, y)
{
	
}

void Pistol::use(Sprite* actor, SDL_Point handPos, int useDir)
{
	this->actor = actor;
	fireDirection = useDir;
	fired = true;
	position.x = handPos.x;
	position.y = handPos.y;
	position.w = 32;
	position.h = 32;
}

Attack* Pistol::getAttack() // TODO: NEEDS TO KNOW HOW MUCH TIME HAS PASSED
{
	if (fired && framesSinceShot >= COOL_OFF)
	{
		//framesSinceShot = 0;
		//SDL_Rect position, int dir, Sprite* attacker, Item* weapon
		return new Bullet(position, fireDirection, actor, this);
	}
	fired = false;
}