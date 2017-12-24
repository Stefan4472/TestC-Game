/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, standard IO, and strings
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include "player_sprite.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

SDL_Surface *player_idle_img = NULL, *player_mvup_img = NULL, *player_mvdown_img = NULL, *player_mvright_img = NULL, *player_mvleft_img = NULL;

bool init()
{
		//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;
	
	player_idle_img = loadSurface("graphics/player_idle_spritesheet.bmp");
	player_mvup_img = loadSurface("graphics/player_mvup_spritesheet.bmp");
	player_mvdown_img = loadSurface("graphics/player_mvdown_spritesheet.bmp");
	player_mvright_img = loadSurface("graphics/player_mvright_spritesheet.bmp");
	player_mvleft_img = loadSurface("graphics/player_mvleft_spritesheet.bmp");
	
	return success;
}

void close()
{
	SDL_FreeSurface(player_idle_img);
	SDL_FreeSurface(player_mvup_img);
	SDL_FreeSurface(player_mvdown_img);
	SDL_FreeSurface(player_mvright_img);
	SDL_FreeSurface(player_mvleft_img);
	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

SDL_Surface* loadSurface( std::string path )
{
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}

	return loadedSurface;
}


int main( int argc, char* args[] )
{
	printf("Hello from main\n");
	init();
	printf("Initialized\n");
	loadMedia();
	printf("Loaded Media\n");
	PlayerSprite playerSprite = PlayerSprite(100.0f, 140.0f, player_idle_img, player_mvup_img, player_mvdown_img, player_mvleft_img, player_mvright_img);
	printf("Created player sprite\n");
	
	//Main loop flag
	bool quit = false;
	bool paused = false;
	
	Uint32 last_frame_ticks = SDL_GetTicks(); 
	Uint32 ticks_since_last_frame;
	
	//Event handler
	SDL_Event e;

	//While application is running
	while( !quit )
	{
		// calculate number of milliseconds since last frame was rendered 
		ticks_since_last_frame = SDL_GetTicks() - last_frame_ticks;
		printf("%d ticks since last frame\n", ticks_since_last_frame);
		//printf("In game loop");
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//printf("Handling Input");
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			// first send event to playerSprite, which will handle it in almost all cases.
			else if (!playerSprite.handleKeyEvent(e)) {
				// process if playerSprite didn't handle it
				printf("PlayerSprite did not handle--checking on main thread\n");
				switch( e.key.keysym.sym )
				{ 
					case SDLK_p: // pause/unpause on "p"
						if (e.type == SDL_KEYDOWN && !paused) {
							printf("Pausing\n");
							paused = true;
						} else if (e.type == SDL_KEYUP) {
							printf("Unpausing\n");
							paused = false;
						}
						break;
					
					case SDLK_ESCAPE:
					case SDLK_q: // quit on ESC or "q" key
						quit = true;
						break;
				}
			}
			// update last_frame_ticks
			last_frame_ticks += ticks_since_last_frame;
		}

		playerSprite.passTime(0.03f);
		
		// draw white background todo: background
		SDL_FillRect( gScreenSurface, NULL, SDL_MapRGB( gScreenSurface->format, 0xFF, 0xFF, 0xFF ) );
		
		//SDL_BlitSurface( player_idle_img, NULL, gScreenSurface, NULL );
		
		//Apply the current image
		//SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );

		playerSprite.drawTo(gScreenSurface);
		
		//Update the surface
		SDL_UpdateWindowSurface( gWindow );
	}

	//Free resources and close SDL
	close();

	return 0;
}