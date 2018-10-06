// testing the FontAtlas, which supports rendering/drawing text in various fonts and sizes
// g++ test/test_font_atlas.cpp engine/font_atlas.cpp engine/rendered_char_spec.cpp engine/loaded_font_spec.cpp -o test_font_atlas -Iengine -I. -lSDL2 -lSDL2_image -lSDL2_ttf -std=c++11
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include "font_ids.h"
#include "font_atlas.h"

using namespace std;

bool init();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
FontAtlas* fontAtlas = NULL;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

int main(int argc, char* argv[])
{
  init();
  fontAtlas = new FontAtlas();

  fontAtlas->drawTextTo(gRenderer, "Hello World", 100, 100, FontId::JOYSTIX, 20);

  // render screen
  SDL_RenderPresent(gRenderer);

  sleep(10);

  close();
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
  gWindow = SDL_CreateWindow("FontAtlas Test", SDL_WINDOWPOS_UNDEFINED,
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

  // initialize fonts
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		return false;
	}

	return true;
}

void close()
{
	printf("Close function reached\n");

  delete fontAtlas;
  fontAtlas = NULL;

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

  TTF_Quit();
  printf("Quit TTF\n");

  SDL_Quit();
	printf("Quit SDL\n");
}
