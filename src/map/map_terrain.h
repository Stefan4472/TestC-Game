#ifndef MAP_TERRAIN_H
#define MAP_TERRAIN_H

#include "texture_atlas.h"

// the available types of MapTerrain
enum TerrainType
{
  NONE,
  GRASS,
  BROWN_BRICK,
  DARK_BRICK,
  WHITE_BRICK,
  WATER,
  NUM_TYPES
};

/*
A tile of "terrain" on the map, e.g. grass, brick, water.
A MapTerrain has a textureId used to draw it and a boolean defining whether it
can be walked on by players/NPCs.
TODO: ANIMATION SUPPORT? INTERACTION SUPPORT?
*/
class MapTerrain
{
public:
  TextureId textureId = TextureId:TEXTURE_NONE;
  bool walkable = false;

  // pre-defined MapTerrain types. Defined in map_terrain.cpp
  static const NONE;
  static const GRASS;
  static const BROWN_BRICK;
  static const DARK_BRICK;
  static const WHITE_BRICK;
  static const WATER;

  // array linking TerrainType to MapTerrain object
  // defined in map_terrain.cpp
  static const MapTerrain[] MAP_TERRAINS;

  // returns a terrain object of the given type
  static MapTerrain getTerrain(TerrainType type);
};

#endif
