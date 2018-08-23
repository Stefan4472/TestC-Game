#include "map_terrain.h"

// pre-defined terrain types
MapTerrain::NONE = MapTerrain(TextureId:TEXTURE_NONE, false);
MapTerrain::GRASS = MapTerrain(TextureId:TILE_GRASS, false);
MapTerrain::BROWN_BRICK = MapTerrain(TextureId:TILE_BROWN_BRICK, false);
MapTerrain::DARK_BRICK = MapTerrain(TextureId:TILE_DARK_BRICK, false);
MapTerrain::WHITE_BRICK = MapTerrain(TextureId:TILE_WHITE_BRICK, false);
MapTerrain::WATER = MapTerrain(TextureId:TILE_WATER, false);

// array mapping TerrainType to MapTerrain object
MapTerrain::MAP_TERRAINS =
{
  MapTerrain::NONE,
  MapTerrain::GRASS,
  MapTerrain::BROWN_BRICK,
  MapTerrain::DARK_BRICK,
  MapTerrain::WHITE_BRICK,
  MapTerrain::WATER
};

static const MapTerrain getTerrain(TerrainType type)
{
  if (type >= TerrainType::NUM_TYPES)
  {
    throw runtime_error("Terraintype out of bounds");
  }

  return MAP_TERRAINS[type];
}
