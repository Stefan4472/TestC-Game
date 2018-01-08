#include "item.h"

Item::Item(TextureAtlas* textureAtlas, int itemType)
{
	this->textureAtlas = textureAtlas;
	this->textureId = ITEM_IMAGES[itemType];
	this->itemType = itemType;
	name = ITEM_NAMES[itemType];
	description = ITEM_NAMES[itemType];
}
/*void Item::handleInteract(Sprite* sprite)
{
	// default: put item in sprite's inventory
	printf("Item handling interact with Sprite\n");
	sprite->inventory->addItem(this);
}*/

const char* Item::getName() 
{
	return name.c_str();	
}

void Item::setPosition(float x, float y)
{
	hitbox.x = x;
	hitbox.y = y;
}

void Item::drawToMap(SDL_Surface* screenSurface, int offsetX, int offsetY)
{
	textureAtlas->draw(screenSurface, textureId, hitbox.x - offsetX, hitbox.y - offsetY);
}

void Item::drawToInventory(SDL_Surface* screenSurface, SDL_Rect dest)
{
	textureAtlas->draw(screenSurface, textureId, 0, 0);
}