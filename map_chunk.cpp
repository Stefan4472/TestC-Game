#include "map_chunk.h"

MapChunk::MapChunk(int seed)
{
	for (int i = 0; i < mapRows; i++)
	{
		for (int j = 0; j < mapCols; j++)
		{
			mapTiles[i][j] = TILE_GRASS;
		}
	}
	
	// figure out which tiles are walkable
	for (int i = 0; i < mapRows; i++) 
	{
		for (int j = 0; j < mapCols; j++) 
		{
			if (mapTiles[i][j] != TILE_WATER)
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