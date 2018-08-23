#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "map_chunk.h"
#include "map_terrain.h"

using namespace std;

/*
Renders and returns chunks for the given chunk index (e.g. (10, -4)).
Can load a map file.
If, for whatever reason, a requested chunk is "out of bounds", the MapGenerator
will return a chunk of empty terrain (MapTerrain::NONE).
THe MapGenerator does not cache rendered chunks--that is the responsibility of
the implementing object.

DESIRED IMPLEMENTATION:
A MAP IS DEFINED BY A DIRECTORY
EACH CHUNK IS STORED IN A SEPERATE FILE, "[x]_[y].chunk"
*/
class MapGenerator
{
public:
  // buffer size for reading in a chunk
  static const size_t CHUNK_BUFFER_SIZE = MapChunk::TILE_ROWS * MapChunk::TILE_COLS + 1;
  // buffer for reading in a chunk file
  char chunkBuffer[BUFFER_SIZE];
  // size of the buffer used to generate file paths for reading map files
  static const size_t FILEPATH_BUFFER_SIZE = 400;
  // buffer used for generating file paths
  char filepathBuffer[FILEPATH_BUFFER_SIZE];
  // path to the directory which stores all the map files
  string mapDir;
  // seed used for random number generator, which generates new chunks if they
  // aren't specified in the map files. Set to 0 to prevent generating new chunks
  int mapSeed = 0;

  // create the map with a path to the map directory and a seed for generating
  // new chunks. Set seed to 0 to prevent generating new chunks and only use
  // those defined in the map files
  MapGenerator(string mapDir, int seed=0);
  // generates and returns MapChunk at the given chunk index
  MapChunk generate(int chunkX, int chunkY);

  // NOTE: CLOSES THE FILE HANDLE
  MapChunk readChunkFile(FILE* file);
  void writeChunkFile(int chunkX, int chunkY, MapChunk chunk);
};
#endif
