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

// corresponding names of MapObjectTypes. Defined in map_object.cpp
// used for debugging
extern const string OBJECT_NAMES[5];

/*
Basically, anything on the map that isn't a terrain tile, a drop, or an NPC.
Usually interactible. TODO: WILL BE USED SOON
*/
class MapObject
{
	public:
		// coordinates RELATIVE TO CHUNK TOP-LEFT. These coordinates specify the
		// top-left of the terrain tile where this object is "planted". The object
		// may plan its drawing around this point.
		int x, y;
		MapObjectType objectType;
		bool walkable;
		SDL_Rect drawRegion;
		int hitChunksWide, hitChunksTall;

    // returns name of the given object. Looks up MapObjectType in OBJECT_NAMES
    static string getName(MapObject* object);

		// TODO: WHAT KIND OF CONSTRUCTOR MAKES SENSE?
		MapObject();

		// draw object to the renderer. Passes (x,y) map coordinates of chunk
		// top-left. This is because MapObjects store their location relative to
		// the top-left cornder of the chunk they are in.
		virtual void drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas,
			int chunkOriginX, int chunkOriginY) = 0;
		// save object to given byte buffer. maxSize is the maximum number of bytes_
		// the representation can take, Return the number of bytes written, starting
		// from index zero
		virtual int saveToByteStream(char bytes[], size_t maxSize) = 0;
		// populate object TODO: THESE WILL NEED TO BE STATIC FACTORY METHODS
		// virtual bool restoreFromByteStream(char bytes[], size_t numBytes) = 0;

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
