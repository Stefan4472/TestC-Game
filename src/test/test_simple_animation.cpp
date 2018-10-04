// tests simple_animation

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "texture_atlas.h"
#include "constants.h"
#include "simple_animation.h"

bool init();
bool loadMedia();
SDL_Texture* loadTexture(std::string path);
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* textureAtlasImg = NULL;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main()
{
  init();
  loadMedia();
  TextureAtlas t_atlas = TextureAtlas(textureAtlasImg);

  SimpleAnimation anim_1(AnimationId::PLAYER_WALK_RIGHT);

  Uint32 last_time = SDL_GetTicks();
	Uint32 curr_time, ticks_since_last_frame;
	int frames = 0;
  bool quit = false;
	SDL_Event e;

	// main loop
	while (!quit)
	{
    frames++;

		// calculate number of milliseconds since last frame was rendered
		curr_time = SDL_GetTicks();
		ticks_since_last_frame = curr_time - last_time;

    // wipe screen
    SDL_Rect screen_background { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderFillRect(gRenderer, &screen_background);


    t_atlas->drawAnim(gRenderer, &anim_1, 50, 50);

		// update screen
		SDL_RenderPresent(gRenderer);

		// update last_frame_ticks
		last_time = curr_time;
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

	// set texture filtering to linear
	if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
		printf( "Warning: Linear texture filtering not enabled!" );
	}

	// create window
  gWindow = SDL_CreateWindow( "Animation Test", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( gWindow == NULL )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

	// create renderer for window
	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
	if( gRenderer == NULL )
	{
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

	// initialize renderer color
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );

	// initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
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
