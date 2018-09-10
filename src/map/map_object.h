#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

#include <SDL/SDL2.h>
#include "texture_atlas.h"
#include "sprite.h"
#include "item.h"
#include "item_drop.h"
#include "sound.h"

using namespace std;

/*
Basically, anything on the map that isn't a terrain tile, a drop, or an NPC.
Usually interactible. TODO: WILL BE USED SOON
*/
class MapObject
{
	public:
		SDL_Rect drawRegion;
		SDL_Rect mapHitbox;  // TODO: TILE-BASED HITBOX

		virtual void update(int ms) = 0;
		virtual void onInteract(Sprite* sprite, Item* inHand) = 0;
		virtual void getAndClearDrops(vector<ItemDrop> drops) = 0;
		virtual void getAndClearSounds(vector<Sound> sounds) = 0;
		virtual void drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas,
			int offsetX, int offsetY) = 0;

		MapObject(TextureAtlas* textureAtlas, TextureId textureId, int x, int y);
		int x, y, w, h;
		TextureId textureId;
};

#endif
