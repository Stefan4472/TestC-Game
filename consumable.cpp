#include "consumable.h"

Consumable::Consumable(int itemType, float x, float y, TextureAtlas* textureAtlas) : Item(textureAtlas, itemType)
{
	hitbox.x = x;
	hitbox.y = y;
	hitbox.w = textureAtlas->getWidth(textureId);
	hitbox.h = textureAtlas->getHeight(textureId);
	
	switch (itemType)
	{
		case ITEM_BREAD_LOAF:
			healValue = BREAD_HEALING;
			break;
			
		case ITEM_CHICKEN_LEG:
			healValue = CHICKENLEG_HEALING;
			break;
			
		case ITEM_BEER_MUG:
			healValue = BEERMUG_HEALING;
			break;
			
		case ITEM_GREEN_POTION:
			healValue = GREENPOTION_HEALING;
			break;
	}
}

Action* Consumable::consume()
{
	return new HealthRegenAction(healValue, 10);
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