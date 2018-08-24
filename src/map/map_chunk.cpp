#include "map_chunk.h"

MapChunk MapChunk::getNullChunk()
{
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
	MapChunk rand_chunk;
	for (int i = 0; i < TILE_ROWS; i++)
	{
		for (int j = 0; j < TILE_COLS; j++)
		{
			// generate a random number within the terrain types
			rand_chunk.terrain[i][j] = MapTerrain::getTerrain(rand() % TerrainType::NUM_TYPES);
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
