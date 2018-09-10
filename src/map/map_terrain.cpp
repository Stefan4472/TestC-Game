#include "map_terrain.h"

// static MapTerrain MapTerrain::TEST = MapTerrain(TextureId::TEXTURE_NONE, true)

// pre-defined terrain types
MapTerrain MapTerrain::NONE = MapTerrain(TextureId::TEXTURE_NONE, false, TerrainType::NONE);
MapTerrain MapTerrain::GRASS = MapTerrain(TextureId::TILE_GRASS, true, TerrainType::GRASS);
MapTerrain MapTerrain::BROWN_BRICK = MapTerrain(TextureId::TILE_BROWN_BRICK, true, TerrainType::BROWN_BRICK);
MapTerrain MapTerrain::DARK_BRICK = MapTerrain(TextureId::TILE_DARK_BRICK, true, TerrainType::DARK_BRICK);
MapTerrain MapTerrain::WHITE_BRICK = MapTerrain(TextureId::TILE_WHITE_BRICK, true, TerrainType::WHITE_BRICK);
MapTerrain MapTerrain::WATER = MapTerrain(TextureId::TILE_WATER, true, TerrainType::WATER);

// array mapping TerrainType to MapTerrain object
MapTerrain MapTerrain::MAP_TERRAINS[] =
{
  MapTerrain::NONE,
  MapTerrain::GRASS,
  MapTerrain::BROWN_BRICK,
  MapTerrain::DARK_BRICK,
  MapTerrain::WHITE_BRICK,
  MapTerrain::WATER
};

MapTerrain::MapTerrain()
{
  textureId = TextureId::TEXTURE_NONE;
  walkable = false;
  typeId = TerrainType::NONE;
}

MapTerrain::MapTerrain(TextureId textureId, bool walkable, TerrainType typeId)
{
    this->textureId = textureId;
    this->walkable = walkable;
    this->typeId = typeId;
}

MapTerrain MapTerrain::getTerrain(int terrainType)
{
  if (terrainType < 0 || terrainType >= TerrainType::NUM_TYPES)
  {
    throw runtime_error("Terraintype out of bounds");
  }

  return MAP_TERRAINS[terrainType];
}
