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
	
	player_idle_img = loadSurface("player_sprite.bmp");
	player_mvup_img = loadSurface("player_mvup_spritesheet.bmp");
	player_mvdown_img = loadSurface("player_mvdown_spritesheet.bmp");
	player_mvright_img = loadSurface("player_mvright_spritesheet.bmp");
	player_mvleft_img = loadSurface("player_mvleft_spritesheet.bmp");
	
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
	init();
	loadMedia();
	PlayerSprite playerSprite = PlayerSprite(100, 140, player_idle_img, player_mvup_img, player_mvdown_img, player_mvleft_img, player_mvright_img);
	//Main loop flag
	bool quit = false;
	bool pause = false;

	//Event handler
	SDL_Event e;

	//While application is running
	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			//User presses a key
			else if( e.type == SDL_KEYDOWN )
			{
				// send event to playerSprite, which will handle it in almost all cases.
				if (!playerSprite.handleKeyEvent(e)) {
					switch( e.key.keysym.sym )
					{ 

					// this switch-case only runs if the playerSprite did not use the input.
					case SDLK_p: // todo: pause on "p" key
						printf("Pausing\n");
						pause = true;
						break;

					case SDLK_ESCAPE || SDLK_q: // quit on ESC or "q" key
						quit = true;
						break;
					}
				}
			}
		}

		// draw white background todo: background
		SDL_FillRect( gScreenSurface, NULL, SDL_MapRGB( gScreenSurface->format, 0xFF, 0xFF, 0xFF ) );
		
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