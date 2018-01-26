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