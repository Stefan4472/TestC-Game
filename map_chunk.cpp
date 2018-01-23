#include "map_chunk.h"

MapChunk::MapChunk(int seed)
{
	// figure out which tiles are walkable
	for (int i = 0; i < mapRows; i++) 
	{
		for (int j = 0; j < mapCols; j++) 
		{
			if (mapTiles[i][j] != TILE_WATER && objectTiles[i][j] == TEXTURE_NONE)
			{
				walkableTiles[i][j] = true;
			} 
			else 
			{
				walkableTiles[i][j] = false;
			}
		}
	}
	for (int i = 0; i < mapRows; i++)
	{
		for (int j = 0; j < mapCols; j++)
		{
			printf("%d", walkableTiles[i][j]);
		}
		printf("\n");
	}
}