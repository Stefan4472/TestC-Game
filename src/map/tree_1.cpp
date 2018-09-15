#include "tree_1.h"

Tree1::Tree1(int x, int y) : MapObject()
{
  this->x = x;
  this->y = y;
  objectType = MapObjectType::TREE_1;
  walkable = false;
  // TODO: HOW TO INIT DRAW REGION?
  // the image is 72 x 112. Tiles are 32x32
  drawRegion = SDL_Rect { x - (72 - 32) / 2, y - (112 - 32), 72, 112 };
  hitChunksWide = 1;
  hitChunksTall = 1;
}

void Tree1::drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas,
  int chunkOriginX, int chunkOriginY)
{
  drawRegion.x = chunkOriginX + x - (72 - 32) / 2;
  drawRegion.y = chunkOriginY + y - (112 - 32) / 2;
  textureAtlas->drawImg(renderer, TextureId::OBJECT_TREE_1,
    drawRegion.x, drawRegion.y);
}
