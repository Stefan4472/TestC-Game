#include "map_chunk.h"

MapChunk::MapChunk()
{
	objects.push_back(new Tree1(100, 100));
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

void MapChunk::drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas, int x, int y)
{  // TODO: CLIP BOUNDARIES
	// CLIP BOUNDARIES: FIGURE OUT STARTING I,J (INSTEAD OF USING 0, 0)

	printf("Drawing MapChunk to %d, %d\n", x, y);
	// drawing coordinates
	int draw_x, draw_y = y;

	// draw terrain tiles
	for (int i = 0; i < MapChunk::TILE_ROWS; i++)
	{
		draw_x = x;
		for (int j = 0; j < MapChunk::TILE_COLS; j++)
		{
			textureAtlas->drawImg(renderer, terrain[i][j].textureId, draw_x, draw_y);
			draw_x += 32;
		}
		draw_y += 32; // TODO: DON'T HARDCODE TILE WIDTH/HEIGHT
	}

	// draw map objects
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->drawTo(renderer, textureAtlas, x, y);
	}
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
