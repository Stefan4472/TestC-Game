// tests controller adapter via keyboard input

#include <SDL2/SDL.h>
#include <stdio.h>
#include "controller_adapter.h"

bool init();
void close();

SDL_Window* gWindow = NULL;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// test listener class
class TestControlReceiver : public ControllerListener
{
  void onControlStart(GAME_CONTROLS gameControl)
  {
    printf("Control %d started\n", gameControl);
  }

  void onControlEnd(GAME_CONTROLS gameControl)
  {
    printf("Control %d ended\n", gameControl);
  }
};

int main()
{
  init();
  ControllerAdapter control_adapter;
  TestControlReceiver receiver;
  control_adapter.setListener(&receiver);

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

      }
		}
	}

  close();

}

bool init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
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
  return true;
}

void close()
{
	// destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	printf("Destroyed Window\n");

  SDL_Quit();
	printf("Quit SDL\n");
}
