#ifndef MAP_TERRAIN_H
#define MAP_TERRAIN_H

#include <stdexcept>
#include "texture_atlas.h"

using namespace std;

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
  MapTerrain(TextureId textureId, bool walkable);
  
  TextureId textureId = TextureId::TEXTURE_NONE;
  bool walkable = false;

  // pre-defined MapTerrain types. Defined in map_terrain.cpp
  static const MapTerrain NONE;
  static const MapTerrain GRASS;
  static const MapTerrain BROWN_BRICK;
  static const MapTerrain DARK_BRICK;
  static const MapTerrain WHITE_BRICK;
  static const MapTerrain WATER;

  // array linking TerrainType to MapTerrain object
  // defined in map_terrain.cpp
  static const MapTerrain MAP_TERRAINS[];

  // returns a terrain object of the given type
  static const MapTerrain getTerrain(int terrainType);
};

#endif
