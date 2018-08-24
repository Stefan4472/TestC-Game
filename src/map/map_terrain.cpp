#include "map_terrain.h"

// pre-defined terrain types
MapTerrain const MapTerrain::NONE = MapTerrain(TextureId::TEXTURE_NONE, false);
MapTerrain const MapTerrain::GRASS = MapTerrain(TextureId::TILE_GRASS, false);
MapTerrain const MapTerrain::BROWN_BRICK = MapTerrain(TextureId::TILE_BROWN_BRICK, false);
MapTerrain const MapTerrain::DARK_BRICK = MapTerrain(TextureId::TILE_DARK_BRICK, false);
MapTerrain const MapTerrain::WHITE_BRICK = MapTerrain(TextureId::TILE_WHITE_BRICK, false);
MapTerrain const MapTerrain::WATER = MapTerrain(TextureId::TILE_WATER, false);

// array mapping TerrainType to MapTerrain object
MapTerrain const MapTerrain::MAP_TERRAINS[] =
{
  MapTerrain::NONE,
  MapTerrain::GRASS,
  MapTerrain::BROWN_BRICK,
  MapTerrain::DARK_BRICK,
  MapTerrain::WHITE_BRICK,
  MapTerrain::WATER
};

MapTerrain::MapTerrain(TextureId textureId, bool walkable)
{
    this->textureId = textureId;
    this->walkable = walkable;
}

static const MapTerrain MapTerrain::getTerrain(int terrainType)
{
  if (terrainType < 0 || terrainType >= TerrainType::NUM_TYPES)
  {
    throw runtime_error("Terraintype out of bounds");
  }

  return MAP_TERRAINS[terrainType];
}
