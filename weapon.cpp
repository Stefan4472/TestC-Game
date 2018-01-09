#include "weapon.h"

Weapon::Weapon(int itemType, float x, float y, TextureAtlas* textureAtlas) : Item(textureAtlas, itemType)
{
	hitbox.x = x;
	hitbox.y = y;
	hitbox.w = textureAtlas->getWidth(textureId);
	hitbox.h = textureAtlas->getHeight(textureId);
}

Attack* Weapon::use()
{
	return new Attack(10);
}