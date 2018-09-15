#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

#include <SDL2/SDL.h>
#include "texture_atlas.h"
//#include "sprite.h"
//#include "item.h"
//#include "item_drop.h"
//#include "sound.h"

using namespace std;

// the available types of MapObjects
enum class MapObjectType
{
  NONE,
  TREE_1,
	TREE_2,
	ROCK_1,
	ROCK_2
};

/*
Basically, anything on the map that isn't a terrain tile, a drop, or an NPC.
Usually interactible. TODO: WILL BE USED SOON
*/
class MapObject
{
	public:
		// coordinates RELATIVE TO CHUNK TOP-LEFT
		int x, y;
		MapObjectType objectType;
		bool walkable;

		// draw object to the renderer. Passes (x,y) map coordinates of chunk
		// top-left. This is because MapObjects store their location relative to
		// the top-left cornder of the chunk they are in.
		virtual void drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas,
			int chunkOriginX, int chunkOriginY) = 0;
		// virtual int saveToByteStream(char bytes[], int maxSize)
		// virtual void restoreFromByteStream(char bytes[])

	/*	SDL_Rect drawRegion;
		SDL_Rect mapHitbox;  // TODO: TILE-BASED HITBOX

		virtual void update(int ms) = 0;
		virtual void onInteract(Sprite* sprite, Item* inHand) = 0;
		virtual void getAndClearDrops(vector<ItemDrop> drops) = 0;
		virtual void getAndClearSounds(vector<Sound> sounds) = 0;


		MapObject(TextureAtlas* textureAtlas, TextureId textureId, int x, int y);
		int x, y, w, h;
		TextureId textureId;
		*/
};

#endif
