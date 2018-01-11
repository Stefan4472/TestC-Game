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

void Consumable::use(SDL_Point handPos, int useDir)
{
	//return new HealthRegenAction(healValue, 10);
	destroy = true;
}

Action* Consumable::getBuff()
{
	return new HealthRegenAction(healValue, healValue * 100);	
}