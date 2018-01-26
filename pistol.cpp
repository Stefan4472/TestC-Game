#include "pistol.h"

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