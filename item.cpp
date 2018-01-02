#include "item.h"

void Item::init(SDL_Surface* sprite, SDL_Surface* invWidget, float x, float y)
{
	this->sprite = sprite;
	inventoryWidget = invWidget;
	hitbox.x = x;
	hitbox.y = y;
	hitbox.w = sprite->w;
	hitbox.h = sprite->h;
	dest.w = hitbox.w;
	dest.h = hitbox.h;
	printf("Hitbox %d, %d w/h %d, %d\n", hitbox.x, hitbox.y, hitbox.w, hitbox.h);
	printf("Dest %d, %d w/h %d, %d\n", dest.x, dest.y, dest.w, dest.h);
}

void Item::drawToMap(SDL_Surface* screenSurface, int offsetX, int offsetY)
{
	dest.x = hitbox.x - offsetX;
	dest.y = hitbox.y - offsetY;
	printf("Drawing pickup at %d, %d with w/h %d, %d\n", dest.x, dest.y, dest.w, dest.h);
	SDL_BlitSurface(sprite, &hitbox, screenSurface, &dest ); // todo: Sets dest w/h to zero
	printf("Dest now %d, %d with w/h %d, %d\n", dest.x, dest.y, dest.w, dest.h);
}

void Item::drawToInventory(SDL_Surface* screenSurface, SDL_Rect dest)
{
	
}