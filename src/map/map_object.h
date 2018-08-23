#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

#include "texture_atlas.h"
/*
Basically, anything on the map that isn't a terrain tile, a drop, or an NPC.
Usually interactible. TODO: WILL BE USED SOON
*/

class MapObject
{
	public:
		MapObject(TextureAtlas* textureAtlas, TextureId textureId, int x, int y);
		int x, y, w, h;
		TextureId textureId;
};

#endif
