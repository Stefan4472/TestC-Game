#include "weapon.h"

Weapon::Weapon(int itemType, float x, float y, TextureAtlas* textureAtlas) : Item(textureAtlas, itemType)
{
	hitbox.x = x;
	hitbox.y = y;
	hitbox.w = textureAtlas->getWidth(textureId);
	hitbox.h = textureAtlas->getHeight(textureId);
}

void Weapon::use(SDL_Rect position)
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

void Sword::use(SDL_Rect position)
{
	hitbox.x = position.x;
	hitbox.y = position.y;
	hitbox.w = position.w;
	hitbox.h = position.h;
}

Attack* Sword::getAttack()
{
	return new Attack(10, hitbox);
}