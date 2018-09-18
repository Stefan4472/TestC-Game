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

	// add a few trees to test out
	rand_chunk.addObject(new Tree1(100, 200));
	rand_chunk.addObject(new Tree1(200, 200));
	rand_chunk.addObject(new Tree1(300, 250));

	return rand_chunk;
}

bool MapChunk::addObject(MapObject* object)
{
	printf("Adding a %s at %d, %d\n", MapObject::getName(object).c_str(),
		object->x, object->y);

	// calculate tile the top-left of the object sits on
	int tile_i = object->x / 32;
	int tile_j = object->y / 32;

	// check that the object can be placed without overlapping another object
	for (int i = 0; i < object->hitChunksTall; i++)
	{
		for (int j = 0; j < object->hitChunksWide; j++)
		{
			if (objectHitTiles[tile_i + i][tile_j + j])
			{
				return false;
			}
		}
	}

	// no overlap: add object and update mappings
	objects.push_back(object);

	for (int i = 0; i < object->hitChunksTall; i++)
	{
		for (int j = 0; j < object->hitChunksWide; j++)
		{
			objectHitTiles[tile_i + i][tile_j + j] = object;
			walkable[tile_i + i][tile_j + j] = object;
		}
	}
}

int MapChunk::numObjects()
{
	return objects.size();
}

MapObject* MapChunk::getObject(int index)
{
	if (index > -1 && index < objects.size())
	{
		return objects[index];
	}
	else
	{
		throw runtime_error("Index Out of Bounds");
	}
}

void MapChunk::addDrop(ItemDrop* drop)
{

}

int MapChunk::numDrops()
{
	printf("Using numDrops(), which hasn't been implemented yet\n");
	return 0;
}

ItemDrop* getDrop(int tileX, int tileY)
{

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

	// TODO: draw map drops 

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

void MapChunk::updateObjectHitTiles()
{
	// clear current mapping
	for (int i = 0; i < MapChunk::TILE_ROWS; i++)
	{
		for (int j = 0; j < MapChunk::TILE_COLS; j++)
		{
			objectHitTiles[i][j] = NULL;
		}
	}

	// for each object:
	// - determine tile its top left is in
	// - check hitChunksWide and hitChunksTall
	// - set the tiles in that range to the object's pointer
	int tile_x, tile_y;
	MapObject* obj = NULL;
	for (int obj_index = 0; obj_index < objects.size(); obj_index++)
	{
		obj = objects[obj_index];

		tile_x = obj->x / 32;  // TODO: DON'T HARDCODE TILE WIDTH/height
		tile_y = obj->y / 32;

		for (int i = 0; i < obj->hitChunksWide; i++)
		{
			for (int j = 0; j < obj->hitChunksTall; j++)
			{
				objectHitTiles[tile_x + i][tile_y + j] = obj;
			}
		}
	}
}

void MapChunk::updateWalkableMap()
{
	// a tile is walkable if the terrain is walkable and has no pointer to
	// a MapObject
	for (int i = 0; i < MapChunk::TILE_ROWS; i++)
	{
		for (int j = 0; j < MapChunk::TILE_COLS; j++)
		{
			walkable[i][j] = terrain[i][j].walkable && !objectHitTiles[i][j];
		}
	}
}
