#include "item.h"

Item::Item(TextureAtlas* textureAtlas, int textureId, float x, float y)
{
	this->textureAtlas = textureAtlas;
	this->textureId = textureId;
	
	hitbox.x = x;
	hitbox.y = y;
	hitbox.w = textureAtlas->getWidth(textureId);
	hitbox.h = textureAtlas->getHeight(textureId);
}

/*void Item::handleInteract(Sprite* sprite)
{
	// default: put item in sprite's inventory
	printf("Item handling interact with Sprite\n");
	sprite->inventory->addItem(this);
}*/

void Item::drawToMap(SDL_Surface* screenSurface, int offsetX, int offsetY)
{
	textureAtlas->draw(screenSurface, textureId, hitbox.x - offsetX, hitbox.y - offsetY);
}

void Item::drawToInventory(SDL_Surface* screenSurface, SDL_Rect dest)
{
	textureAtlas->draw(screenSurface, textureId, 0, 0);
}