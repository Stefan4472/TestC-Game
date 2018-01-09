#include "weapon.h"

Weapon::Weapon(int itemType, float x, float y, TextureAtlas* textureAtlas) : Item(textureAtlas, itemType)
{
	hitbox.x = x;
	hitbox.y = y;
	hitbox.w = textureAtlas->getWidth(textureId);
	hitbox.h = textureAtlas->getHeight(textureId);
}

void Weapon::use()
{
	//return new Attack(10);
}

/*Sword::Sword(TextureAtlas* textureAtlas, float x, float y) : Item(textureAtlas, ITEM_SWORD)
{
	hitbox.x = x;
	hitbox.y = y;
	hitbox.w = textureAtlas->getWidth(textureId);
	hitbox.h = textureAtlas->getHeight(textureId);
}

Action* Sword::use()
{
	// place holder
	return new HealthRegenAction(1, 1);
}*/