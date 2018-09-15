#include "map_chunk.h"

MapChunk::MapChunk()
{

}

MapChunk MapChunk::getNullChunk()
{
	printf("MapChunk: generating NULL Chunk\n");
	MapChunk null_chunk;
	for (int i = 0; i < TILE_ROWS; i++)
	{
		for (int j = 0; j < TILE_COLS; j++)
		{
			null_chunk.terrain[i][j] = MapTerrain::NONE;
		}
	}
	return null_chunk;
}

MapChunk MapChunk::getRandomChunk()
{
	printf("MapChunk: generating random Chunk\n");
	MapChunk rand_chunk;
	for (int i = 0; i < TILE_ROWS; i++)
	{
		for (int j = 0; j < TILE_COLS; j++)
		{
			// generate a random number 0 < n < num_terrain_types
			rand_chunk.terrain[i][j] =
				MapTerrain::getTerrain(1 + rand() % (TerrainType::NUM_TYPES - 1));
		}
	}
	return rand_chunk;
}

void MapChunk::printDebug()
{
	for (int i = 0; i < TILE_ROWS; i++)
	{
		for (int j = 0; j < TILE_COLS; j++)
		{
			printf("%d ", terrain[i][j]);
		}
		printf("\n");
	}
}
