#include "item.h"

void Item::init(TextureAtlas* textureAtlas, int itemType)
{
	this->textureAtlas = textureAtlas;
	this->textureId = ITEM_IMAGES[itemType];
	this->itemType = itemType;
	name = ITEM_NAMES[itemType];
	description = ITEM_NAMES[itemType];
}

Item::Item(TextureAtlas* textureAtlas, int itemType)
{
	init(textureAtlas, itemType);
}

Item::Item(TextureAtlas* textureAtlas, int itemType, float x, float y)
{	
	init(textureAtlas, itemType);
	
	hitbox.x = x;
	hitbox.y = y;
	hitbox.w = textureAtlas->getWidth(textureId);
	hitbox.h = textureAtlas->getHeight(textureId);
}

const char* Item::getName() 
{
	return name.c_str();	
}

void Item::setPosition(float x, float y)
{
	hitbox.x = x;
	hitbox.y = y;
}

Action* Item::getAction()
{
	return NULL;
}

Action* Item::getBuff()
{
	return NULL;
}

Attack* Item::getAttack()
{
	return NULL;
}

void Item::drawToMap(SDL_Surface* screenSurface, int offsetX, int offsetY)
{
	textureAtlas->draw(screenSurface, textureId, hitbox.x - offsetX, hitbox.y - offsetY);
}

void Item::drawToInventory(SDL_Surface* screenSurface, SDL_Rect dest)
{
	textureAtlas->draw(screenSurface, textureId, 0, 0);
}