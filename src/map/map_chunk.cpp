#include "map_chunk.h"

MapChunk getNullChunk()
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
