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

int Tree1::saveToByteStream(char bytes[], size_t maxSize)
{
  int reqd_bytes = 4;
  if (maxSize < reqd_bytes)
  {
    throw runtime_error("Not enough bytes to write Tree1");
  }

  // write x, y coordinates, two bytes each, base 128
  FileUtil::writeToBuffer(bytes, 0, 2, x, 128);
  FileUtil::writeToBuffer(bytes, 2, 2, y, 128);

  return 4;
}

MapObject* Tree1::restoreFromByteStream(char bytes[], size_t numBytes)
{
  if (numBytes != 4)
  {
    throw runtime_error("Not enough bytes to read Tree1");
  }

  // read x and y, 2 bytes each, base-128
  int x = FileUtil::readFromBuffer(bytes, 0, 2, 128);
  int y = FileUtil::readFromBuffer(bytes, 2, 2, 128);

  return new Tree1(x, y);
}
