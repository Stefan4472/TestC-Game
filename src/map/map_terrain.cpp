#include "map_terrain.h"

// static MapTerrain MapTerrain::TEST = MapTerrain(TextureId::TEXTURE_NONE, true)

// pre-defined terrain types
const MapTerrain MapTerrain::NONE = MapTerrain(TextureId::TEXTURE_NONE, false, TerrainType::NONE);
const MapTerrain MapTerrain::GRASS = MapTerrain(TextureId::TILE_GRASS, true, TerrainType::GRASS);
const MapTerrain MapTerrain::BROWN_BRICK = MapTerrain(TextureId::TILE_BROWN_BRICK, true, TerrainType::BROWN_BRICK);
const MapTerrain MapTerrain::DARK_BRICK = MapTerrain(TextureId::TILE_DARK_BRICK, true, TerrainType::DARK_BRICK);
const MapTerrain MapTerrain::WHITE_BRICK = MapTerrain(TextureId::TILE_WHITE_BRICK, true, TerrainType::WHITE_BRICK);
const MapTerrain MapTerrain::WATER = MapTerrain(TextureId::TILE_WATER, true, TerrainType::WATER);

// array mapping TerrainType to MapTerrain object
const MapTerrain MapTerrain::MAP_TERRAINS[] =
{
  MapTerrain::NONE,
  MapTerrain::GRASS,
  MapTerrain::BROWN_BRICK,
  MapTerrain::DARK_BRICK,
  MapTerrain::WHITE_BRICK,
  MapTerrain::WATER
};

MapTerrain::MapTerrain(TextureId textureId, bool walkable, TerrainType typeId)
{
    this->textureId = textureId;
    this->walkable = walkable;
    this->typeId = typeId;
}

const MapTerrain MapTerrain::getTerrain(int terrainType)
{
  if (terrainType < 0 || terrainType >= TerrainType::NUM_TYPES)
  {
    throw runtime_error("Terraintype out of bounds");
  }

  return MAP_TERRAINS[terrainType];
}
