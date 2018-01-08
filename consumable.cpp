#include "consumable.h"

BreadLoaf::BreadLoaf(TextureAtlas* textureAtlas, float x, float y) : Item(textureAtlas, ITEM_BREAD_LOAF)
{	
	hitbox.x = x;
	hitbox.y = y;
	hitbox.w = textureAtlas->getWidth(textureId);
	hitbox.h = textureAtlas->getHeight(textureId);
}

BeerMug::BeerMug(TextureAtlas* textureAtlas, float x, float y) : Item(textureAtlas, ITEM_BEER_MUG)
{
	hitbox.x = x;
	hitbox.y = y;
	hitbox.w = textureAtlas->getWidth(textureId);
	hitbox.h = textureAtlas->getHeight(textureId);
}