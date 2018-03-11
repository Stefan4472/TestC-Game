#include "item.h"

void Item::init(TextureAtlas* textureAtlas, int itemType)
{
	this->textureAtlas = textureAtlas;
	this->textureId = ITEM_IMAGES[itemType];
	this->itemType = itemType;
	name = ITEM_NAMES[itemType];
	description = ITEM_NAMES[itemType];
	stackSize = ITEM_STACKSIZES[itemType];
}

Item::Item(TextureAtlas* textureAtlas, int itemType)
{
	init(textureAtlas, itemType);
}

Item::Item(TextureAtlas* textureAtlas, int itemType, float x, float y)
{	
	init(textureAtlas, itemType);
	
	position.x = x;
	position.y = y;
	position.w = textureAtlas->getWidth(textureId);
	position.h = textureAtlas->getHeight(textureId);
}

const char* Item::getName() 
{
	return name.c_str();	
}

void Item::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

bool Item::reload(Item* item)
{
	return false;
}

void Item::update(int ms)
{
	return;	
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

void Item::drawTo(SDL_Renderer* renderer, int x, int y)
{
	textureAtlas->draw(renderer, textureId, x, y);	
}

void Item::drawToMap(SDL_Renderer* renderer, int offsetX, int offsetY)
{
	textureAtlas->draw(renderer, textureId, position.x - offsetX, position.y - offsetY);
}

void Item::drawToInventory(SDL_Renderer* renderer, SDL_Rect dest)
{
	textureAtlas->draw(renderer, textureId, 0, 0);
}

int getStackSize(int itemId) 
{
	return ITEM_STACKSIZES[itemId];	
}