#include "map_generator.h"

MapGenerator::MapGenerator(string mapDir, int mapSeed)
{
  this->mapDir = mapDir;
  this->mapSeed = mapSeed;
}

MapChunk MapGenerator::generate(int chunkX, int chunkY)
{
  // create cstring with file path to the chunk file
  snprintf(filepathBuffer, FILEPATH_BUFFER_SIZE, "%s/%d_%d.chunk", mapDir.c_str(),
    chunkX, chunkY);
  printf("Generated file path is %s\n", filepathBuffer);

  // attempt to open file in byte mode
  FILE* file_handle = fopen(filepathBuffer, "rb");

  if (file_handle)  // create the chunk
  {
    return readChunkFile(file_handle);
  }
  else if (mapSeed)  // no chunk exists: generate it
  {
    return MapChunk::getRandomChunk();
  }
  else  // no chunk exists, and no seed set: return NULL chunk
  {
    return MapChunk::getNullChunk();
  }
}

MapChunk MapGenerator::readChunkFile(FILE* file)
{
  // read the file into the buffer
  size_t bytes_read = fread(chunkBuffer, 1, CHUNK_BUFFER_SIZE, file);
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
        MapTerrain::getTerrain(chunkBuffer[i * MapChunk::TILE_ROWS + j]);
    }
  }

  fclose(file);

  return read_chunk;
}

void MapGenerator::writeChunkFile(int chunkX, int chunkY, MapChunk chunk)
{
  // create cstring with file path to the chunk file
  snprintf(filepathBuffer, FILEPATH_BUFFER_SIZE, "%s/%d_%d.chunk", mapDir.c_str(),
    chunkX, chunkY);
  printf("Generated file path to write chunk is %s\n", filepathBuffer);

  // attempt to open file in byte mode
  // FILE* file_handle = fopen(filepathBuffer, "rb");
  FILE* file_handle = fopen(filepathBuffer, "wb");

  if (!file_handle)  // create the chunk
  {
    throw runtime_error("Couldn't create chunk save file");
  }

  // copy terrain to buffer
  for (int i = 0; i < MapChunk::TILE_ROWS; i++)
  {
    for (int j = 0; j < MapChunk::TILE_COLS; j++)
    {
      chunkBuffer[i * MapChunk::TILE_ROWS + j] = chunk.terrain[i][j].typeId;
    }
  }

  printf("Writing... ");
  for (int i = 0; i < CHUNK_BUFFER_SIZE; i++)
  {
    printf("%d", chunkBuffer[i]);
  }
  printf("\n");

  // write to file
  fwrite(chunkBuffer, 1, CHUNK_BUFFER_SIZE, file_handle);

  fclose(file_handle);

  printf("Done\n");
}
