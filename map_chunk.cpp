#include "map_chunk.h"

MapObject::MapObject(TextureAtlas* textureAtlas, int textureId, int x, int y)
{
	this->textureId = textureId;
	this->x = x;
	this->y = y;
	w = textureAtlas->getWidth(textureId);
	h = textureAtlas->getHeight(textureId);
	printf("MapObject created id %d, x/y %d %d w/h %d %d\n", textureId, x, y, w, h);
}

MapChunk::MapChunk(TextureAtlas* textureAtlas, int seed)
{
	// generate tiles
	for (int i = 0; i < mapRows; i++)
	{
		for (int j = 0; j < mapCols; j++)
		{
			mapTiles[i][j] = TILE_GRASS;
		}
	}

	// generate map objects, aligned with tiles
	objects.push_back(MapObject(textureAtlas, OBJECT_TREE_1, 32 * 6, 32 * 6));
	
	// TODO: SORT OBJECTS BY Y 
	
	// figure out which tiles are walkable
	for (int i = 0; i < mapRows; i++) 
	{
		for (int j = 0; j < mapCols; j++) 
		{
			// set all water tiles to non-walkable
			walkableTiles[i][j] = mapTiles[i][j] != TILE_WATER;
		}
	}
	
	// block off tiles covered by objects
	for (int i = 0; i < objects.size(); i++) 
	{
		int tile_row = objects[i].x / 32;
		int tile_col = objects[i].y / 32;
		int tiles_wide = objects[i].w / 32;
		int tiles_tall = objects[i].h / 32;
		
		for (int j = 0; j < tiles_tall; j++)
		{
			for (int k = 0; k < tiles_wide; k++)
			{
				walkableTiles[tile_row + j][tile_col + k] = false;		
			}
		}
	}
	
	// print walkable tiles
	for (int i = 0; i < mapRows; i++)
	{
		for (int j = 0; j < mapCols; j++)
		{
			printf("%d", walkableTiles[i][j]);
		}
		printf("\n");
	}
}