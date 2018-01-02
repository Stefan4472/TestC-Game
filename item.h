#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <SDL2/SDL.h>

// an item is the base class for anything that can be picked up or kept in inventory.
// it has a sprite, a widget (for display in inventory), a hitbox, and a description
class Item
{
	protected:
		SDL_Surface* sprite;
		SDL_Surface* inventoryWidget;
		SDL_Rect hitbox = {0, 0, 0, 0};
		SDL_Rect dest = {0, 0, 0, 0};
		
	public:
		void init(SDL_Surface* sprite, SDL_Surface* invWidget, float x, float y);
		virtual void drawToMap(SDL_Surface* screenSurface, int offsetX, int offsetY);
		virtual void drawToInventory(SDL_Surface* screenSurface, SDL_Rect dest);
};

#endif