#include "map_generator.h"

MapGenerator(string mapDir, int mapSeed)
{
  this->mapDir = mapDir;
  this->mapSeed = mapSeed;
}

MapChunk MapGenerator::generate(int chunkX, int chunkY)
{
  // create cstring with file path to the chunk file
  snprintf(filepathBuffer, FILEPATH_BUFFER_SIZE, "%s\%d_%d.chunk", mapDir.c_str(),
    chunkX, chunkY);
  printf("Generated file path is %s\n", filepathBuffer);

  // attempt to open file in byte mode
  FILE* file_handle = fopen(filepathBuffer, "rb");

  if (file_handle)  // create the chunk
  {
    return readChunkFile(filepathBuffer);
  }
  else if (mapSeed)  // no chunk exists: generate it
  {
    // TODO: CHUNK GENERATION
    return MapChunk::NONE;
  }
  else  // no chunk exists, and no seed set: return NULL chunk
  {
    return MapChunk::NONE;
  }
}

MapChunk MapGenerator::readChunkFile(FILE* file)
{
  // read the file into the buffer
  size_t bytes_read = fread(chunkBuffer, CHUNK_BUFFER_SIZE, 1, file);
  printf("Read %d bytes\n", bytes_read);

  // make sure the file had the correct amount of data
  if (bytes_read != CHUNK_BUFFER_SIZE)
  {
    throw runtime_error("File did not have the correct amount of data");
  }

  MapChunk read_chunk;

  // read through the bytes, selecting the corresponding terrain
  for (int i = 0; i < MapChunk::TILE_ROWS; i++)
  {
    for (int j = 0; j < MapChunk::TILE_COLS; j++)
    {
      // TODO: ERROR CHECKING?
      read_chunk.terrain[i][j] =
        MapTerrain::getTerrain(chunkBuffer[i * MapChunk::TILE_ROWS + j])
    }
  }

  fclose(file);

  return read_chunk;
}

void MapGenerator::writeChunkFile(int chunkX, int chunkY, MapChunk chunk)
{

}
