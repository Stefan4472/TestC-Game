#ifndef MAP_OBJECT_TREE_1_H
#define MAP_OBJECT_TREE_1_H

#include "map_object.h"

class Tree1 : public MapObject
{
  public:
    Tree1(int x, int y);
    // draw tree to the renderer, given coordinates of chunk's top-left
    void drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas,
      int chunkOriginX, int chunkOriginY);
};

#endif
