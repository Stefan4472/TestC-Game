#include "utils.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

SDL_Surface* loadSurface( std::string path ) {
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}

	return loadedSurface;
}