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
  // default constructor: creates NONE MapTerrain TODO: SHOULD THIS EVEN BE NECESSARY?
  MapTerrain();
  //
  MapTerrain(TextureId textureId, bool walkable, TerrainType typeId);

  TextureId textureId;
  bool walkable;
  TerrainType typeId;

  // returns a terrain object of the given type
  static MapTerrain getTerrain(int terrainType);

  // const static MapTerrain TEST;

  // pre-defined MapTerrain types. Defined in map_terrain.cpp TODO: MAKE CONST
  static MapTerrain NONE;
  static MapTerrain GRASS;
  static MapTerrain BROWN_BRICK;
  static MapTerrain DARK_BRICK;
  static MapTerrain WHITE_BRICK;
  static MapTerrain WATER;

  // array linking TerrainType to MapTerrain object
  // defined in map_terrain.cpp
  static MapTerrain MAP_TERRAINS[];
};

#endif
