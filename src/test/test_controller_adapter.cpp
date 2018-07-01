// tests controller adapter via keyboard input

#include <SDL2/SDL.h>
#include <stdio.h>
#include "controller_adapter.h"

bool init();
void close();

SDL_Window* gWindow = NULL;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main()
{
  init();
  ControllerAdapter control_adapter;
	SDL_Event e;
  bool quit = false;

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
			else if (control_adapter.handleKeyEvent(e))
			{

			}
      else
      {
        printf("Returned false\n");
      }
		}
	}

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

	// create window
  gWindow = SDL_CreateWindow( "Animation Test", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( gWindow == NULL )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

	// // create renderer for window
	// gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
	// if( gRenderer == NULL )
	// {
	// 	printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
	// 	return false;
	// }
  //
	// // initialize renderer color
	// SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
}



void close()
{
	// destroy renderer
	// SDL_DestroyRenderer( gRenderer );
	// gRenderer = NULL;

	printf("Destroyed renderer\n");

	// destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	printf("Destroyed Window\n");

  SDL_Quit();
	printf("Quit SDL\n");
}
