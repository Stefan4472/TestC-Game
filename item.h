#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "texture_atlas.h"

// an item is the base class for anything that can be picked up or kept in inventory.
// it has a sprite, a widget (for display in inventory), a hitbox, and a description
class Item
{
	protected:
		// id for sprite in texture_atlas.h
		int textureId;
		// pointer to TextureAtlas used for drawing
		TextureAtlas* textureAtlas;
		
	public: // todo: make base class
		// defines position of Item on the map
		SDL_Rect hitbox = {0, 0, 0, 0};
		Item(TextureAtlas* textureAtlas, int textureId, float x, float y);
		// handles given sprite interacting with the object on the ground -- removed due to forward declaration errors
		//virtual void handleInteract(Sprite* sprite);
		virtual void drawToMap(SDL_Surface* screenSurface, int offsetX, int offsetY);
		virtual void drawToInventory(SDL_Surface* screenSurface, SDL_Rect dest);
		//virtual void use() = 0;
};

#endif