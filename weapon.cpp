#include "weapon.h"

Weapon::Weapon(int itemType, float x, float y, TextureAtlas* textureAtlas) : Item(textureAtlas, itemType)
{
	hitbox.x = x;
	hitbox.y = y;
	hitbox.w = textureAtlas->getWidth(textureId);
	hitbox.h = textureAtlas->getHeight(textureId);
}

void Weapon::use(SDL_Point handPos, int useDir)
{
	//return new Attack(10);
}

Sword::Sword(TextureAtlas* textureAtlas, float x, float y) : Item(textureAtlas, ITEM_SWORD)
{
	hitbox.x = x;
	hitbox.y = y;
	hitbox.w = textureAtlas->getWidth(textureId);
	hitbox.h = textureAtlas->getHeight(textureId);
}

void Sword::use(SDL_Point handPos, int useDir)
{
	// set hitbox pased on handPosition and direction
	switch (useDir)
	{
		case DIRECTION_RIGHT:		 // todo: this will require tweaking
			hitbox.x = handPos.x;
			hitbox.y = handPos.y - 16;
			break;
			
		case DIRECTION_LEFT:
			hitbox.x = handPos.x - 32;
			hitbox.y = handPos.y - 16;
			break;
			
		case DIRECTION_UP:
			hitbox.x = handPos.x - 16;
			hitbox.y = handPos.y - 32;
			break;
			
		case DIRECTION_DOWN:
			hitbox.x = handPos.x - 16;
			hitbox.y = handPos.y;
			break;
	}
}

Attack* Sword::getAttack()
{
	return new Attack(10, hitbox);
}