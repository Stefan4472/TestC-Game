#include "consumable.h"

BreadLoaf::BreadLoaf(TextureAtlas* textureAtlas, float x, float y) : Item(textureAtlas, ITEM_BREAD_LOAF)
{	
	hitbox.x = x;
	hitbox.y = y;
	hitbox.w = textureAtlas->getWidth(textureId);
	hitbox.h = textureAtlas->getHeight(textureId);
}

Action* BreadLoaf::use()
{
	return new HealthRegenAction(15, 100);
}

BeerMug::BeerMug(TextureAtlas* textureAtlas, float x, float y) : Item(textureAtlas, ITEM_BEER_MUG)
{
	hitbox.x = x;
	hitbox.y = y;
	hitbox.w = textureAtlas->getWidth(textureId);
	hitbox.h = textureAtlas->getHeight(textureId);
}

Action* BeerMug::use()
{
	return new HealthRegenAction(10, 1000);	
}

Sword::Sword(TextureAtlas* textureAtlas, float x, float y) : Item(textureAtlas, ITEM_SWORD)
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
}