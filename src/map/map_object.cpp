#include "map_object.h"

MapObject::MapObject(TextureAtlas* textureAtlas, int textureId, int x, int y)
{
	this->textureId = textureId;
	this->x = x;
	this->y = y;
	w = textureAtlas->getWidth(textureId);
	h = textureAtlas->getHeight(textureId);
	printf("MapObject created id %d, x/y %d %d w/h %d %d\n", textureId, x, y, w, h);
}
