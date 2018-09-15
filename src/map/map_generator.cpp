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

  // read the next byte, which specifies the number of MapObjects stored in the
  if (fread(chunkBuffer, 1, 1, file) != 1)
  {
    printf("NO Objects to Read\n");
    return read_chunk; // TODO: THROW ERROR?
  }

  int num_objects = chunkBuffer[0];
  printf("This file has %d objects\n");

  MapObject* restored = NULL;

  // for each object: read the first char--object type. Read the second byte--
  // number of bytes following. Store those bytes in buffer, and send to the
  // right object reconstructor
  for (int i = 0; i < num_objects; i++)
  {
    printf("Reading object %d:\n");
    if (fread(chunkBuffer, 1, 2, file) != 2)
    {
      printf("Missing first two bytes\n"); // TODO: THROW ERROR?
    }

    int object_type = chunkBuffer[0];
    int num_bytes = chunkBuffer[1];

    // read the specified number of bytes into buffer
    if (fread(chunkBuffer, 1, num_bytes, file) != num_bytes)
    {
      printf("NOT ENOUGH BYTES\n");
    }

    switch (MapObjectType(object_type))
    {
      case MapObjectType::TREE_1:
        restored = Tree1::restoreFromByteStream(chunkBuffer, num_bytes);
        break;
      case MapObjectType::TREE_2:
      case MapObjectType::ROCK_1:
      case MapObjectType::ROCK_2:
        printf("Object Type not implemented yet\n");
        break;
      default:
        printf("Error: unrecognized object type\n");
    }

    if (restored)
    {
      printf("Object successfully recovered\n");
      read_chunk.objects.push_back(restored);
      restored = NULL;
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

  int num_objs = chunk.objects.size();
  printf("Writing %d objects\n");

  // write number of objects
  chunkBuffer[0] = (char) num_objs;
  fwrite(chunkBuffer, 1, 1, file_handle);

  MapObject* map_obj = NULL;
  char num_buffer[1];

  // for each object, convert to bytes and write
  for (int i = 0; i < num_objs; i++)
  {
    printf("Writing object %d\n", i);
    map_obj = chunk.objects[i];

    // write objectType id
    chunkBuffer[0] = char(MapObjectType(map_obj->objectType));
    fwrite(chunkBuffer, 1, 1, file_handle);

    // save object to buffer
    int num_bytes = map_obj->saveToByteStream(chunkBuffer, CHUNK_BUFFER_SIZE);
    num_buffer[0] = char(num_bytes);
    fwrite(num_buffer, 1, 1, file_handle);
    fwrite(chunkBuffer, 1, num_bytes, file_handle);
  }
  fclose(file_handle);

  printf("Done\n");
}
