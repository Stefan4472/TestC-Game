// tests loading and drawing a map
// g++ test/test_map.cpp engine/texture_atlas.cpp map/map_generator.cpp map/map_chunk.cpp map/map_terrain.cpp map/chunk_id.cpp -w -std=c++11 -Iengine -Imap -I. -lSDL2 -lSDL2_image -o test_map

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <unordered_map>
#include "texture_atlas.h"
#include "map_generator.h"
#include "chunk_id.h"

using namespace std;

MapChunk getChunk(int chunkX, int chunkY);
void drawMap();
bool init();
bool loadMedia();
SDL_Texture* loadTexture(std::string path);
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* textureAtlasImg = NULL;
TextureAtlas* textureAtlas = NULL;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

// camera coordinates
int cameraX = -SCREEN_WIDTH / 2;
int cameraY = -SCREEN_HEIGHT / 2;

// mapping of coordinates to loaded chunks
unordered_map<ChunkId, MapChunk> chunkCache;

MapGenerator* mapGenerator = NULL;

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    printf("Expected a single argument (map directory)\n");
    return -1;
  }

  string map_dir = string(argv[1]);
  printf("Running on map directory '%s'\n", map_dir.c_str());

  // create the map generator with the given file path
  mapGenerator = new MapGenerator(map_dir, 0);

  init();
  loadMedia();
  textureAtlas = new TextureAtlas(textureAtlasImg);

  Uint32 last_time = SDL_GetTicks();
	Uint32 curr_time, ticks_since_last_frame;
	int frames = 0;
  bool quit = false;
	SDL_Event e;

	// main loop
	while (!quit)
	{
    frames++;

    // slow down framerate
    sleep(1);

    // calculate number of milliseconds since last frame was rendered
		curr_time = SDL_GetTicks();
		ticks_since_last_frame = curr_time - last_time;

		// handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch( e.key.keysym.sym )
				{
          // move camera position
					case SDLK_UP:
          case SDLK_w:
            cameraY -= 2;
            break;
          case SDLK_DOWN:
          case SDLK_s:
            cameraY += 2;
        		break;
          case SDLK_LEFT:
          case SDLK_a:
            cameraX -= 2;
            break;
          case SDLK_RIGHT:
          case SDLK_d:
            cameraX += 2;
            break;
				}
			}
    }

    drawMap();

		// render screen
		SDL_RenderPresent(gRenderer);

		// update last_frame_ticks
		last_time = curr_time;
	}

  close();
}

MapChunk getChunk(int chunkX, int chunkY)
{
	printf("Map: Request for chunk %d, %d\n", chunkX, chunkY);

	// lookup using ChunkId
	unordered_map<ChunkId, MapChunk>::iterator iterator =
		chunkCache.find(ChunkId(chunkX, chunkY));

	// not found: call MapGenerator.generate() and add to cache
	if (iterator == chunkCache.end())
	{
		printf("Not found in cache: generating...\n");
		MapChunk generated = mapGenerator->generate(chunkX, chunkY);
		chunkCache.emplace(ChunkId(chunkX, chunkY), generated);
		return generated;
	}
	// found: return
	else
	{
		printf("Found in cache: returning...\n");
		return iterator->second;
	}
}

void drawMap()
{
  // draw the terrain
  // row and col of top-left chunk to render
  int start_chunk_x = cameraX / MapChunk::CHUNK_WIDTH;
  int start_chunk_y = cameraY / MapChunk::CHUNK_HEIGHT;

  // offsets from chunk borders on x and y
  int offset_x = cameraX % MapChunk::CHUNK_WIDTH;
  int offset_y = cameraY % MapChunk::CHUNK_HEIGHT;

  // calculate # of chunks to render on width and height of screen (todo: make const)
  int chunks_wide = (SCREEN_WIDTH / MapChunk::CHUNK_WIDTH) + 1;
  int chunks_tall = (SCREEN_HEIGHT / MapChunk::CHUNK_HEIGHT) + 1;

  // check if we need an extra chunk rendered to cover the rest of the screen
  if (MapChunk::CHUNK_WIDTH - offset_x < SCREEN_WIDTH)
  {
    chunks_wide++;
  }
  if (MapChunk::CHUNK_HEIGHT - offset_y < SCREEN_HEIGHT)
  {
    chunks_tall++;
  }

  // coordinates of chunk top-left being drawn
  int chunk_x, chunk_y;
  MapChunk chunk;
  SDL_Rect src, dest;

  // render chunks to canvas, using offsets to get physical coordinates
  for (int chunk_i = 0; chunk_i < chunks_tall; chunk_i++)
  {
    chunk_y = start_chunk_y + chunk_i;
    for (int chunk_j = 0; chunk_j < chunks_wide; chunk_j++)
    {
      chunk_x = start_chunk_x + chunk_j;

      // get the requested MapChunk
      chunk = getChunk(chunk_x, chunk_y);

      // draw each tile from the chunk, at offsets
      for (int i = 0; i < MapChunk::TILE_ROWS; i++)
      {
        dest.y = chunk_i * MapChunk::CHUNK_HEIGHT + i * TILE_HEIGHT - offset_y;
        for (int j = 0; j < MapChunk::TILE_COLS; j++)
        {
          dest.x = chunk_j * MapChunk::CHUNK_WIDTH + j * TILE_WIDTH - offset_x;
          textureAtlas->drawImg(gRenderer, chunk.terrain[i][j].textureId, dest.x, dest.y);
        }
      }
    }
  }
}

bool init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO < 0))
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

	// set texture filtering to linear
	if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
		printf( "Warning: Linear texture filtering not enabled!" );
	}

	// create window
  gWindow = SDL_CreateWindow("MapChunk Test", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (!gWindow)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// create renderer for window
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

  if(!gRenderer)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// initialize renderer color to black
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);

	// initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if(!( IMG_Init( imgFlags ) & imgFlags ))
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}
	return true;
}

bool loadMedia()
{
	textureAtlasImg = loadTexture("/home/student/TestC-Game/graphics/texture_atlas.png");
  if (!textureAtlasImg)
  {
    printf("Couldn't load texture atlas\n");
  }
  return textureAtlasImg != NULL;
}

SDL_Texture* loadTexture(std::string path)
{
	// load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		return NULL;
	}

	SDL_Texture* new_texture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	if (new_texture == NULL)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str());
	}

	// free loaded surface (no longer necessary)
	SDL_FreeSurface(loadedSurface);

	return new_texture;
}

void close()
{
	printf("Close function reached\n");
	SDL_DestroyTexture(textureAtlasImg);
	textureAtlasImg = NULL;

	printf("Destroyed texture atlas\n");

	// destroy renderer
	SDL_DestroyRenderer( gRenderer );
	gRenderer = NULL;

	printf("Destroyed renderer\n");

	// destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	printf("Destroyed Window\n");

	// quit SDL subsystems
	IMG_Quit();
	printf("Quit IMG\n");

  SDL_Quit();
	printf("Quit SDL\n");
}
