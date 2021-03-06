#ifndef MAP_OBJECT_TREE_1_H
#define MAP_OBJECT_TREE_1_H

#include <stdexcept>
#include "map_object.h"
#include "file_io_util.h"

class Tree1 : public MapObject
{
  public:
    Tree1(int x, int y);
    // draw tree to the renderer, given coordinates of chunk's top-left
    void drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas,
      int chunkOriginX, int chunkOriginY);

    int saveToByteStream(char bytes[], size_t maxSize);
		static MapObject* restoreFromByteStream(char bytes[], size_t numBytes);
};

#endif
