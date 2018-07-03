// tests sound_atlas

#include <SDL2/SDL.h>
#include <stdio.h>
#include <unistd.h>
#include "sound_atlas.h"

bool init();
void close();

SDL_Window* gWindow = NULL;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main()
{
  init();
  SoundAtlas soundAtlas;
	SDL_Event e;
  bool quit = false;

  for (int i = 1; i < Sounds::NUM_SOUNDS; i++)
  {
    soundAtlas.playSound(i);
    usleep(500000);
  }

	// main loop
	while (!quit)
	{
		// handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
      else
      {

      }
		}
	}

  close();
}

bool init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

	// create window
  gWindow = SDL_CreateWindow( "Animation Test", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if (gWindow == NULL)
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

  // initialize sound mixer
  if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
  {
   printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
   return false;
  }
  return true;
}



void close()
{
	// destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	printf("Destroyed Window\n");

  // TODO: NEED TO QUIT AUDIO SUBSYSTEM?
  printf("NOT QUITTING AUDIO SUBSYSTEM\n");
  SDL_Quit();
	printf("Quit SDL\n");
}
