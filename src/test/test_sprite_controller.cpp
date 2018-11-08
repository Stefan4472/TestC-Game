// test PlayerController
// g++ test/test_sprite_controller.cpp engine/animation_engine.cpp engine/animation_player.cpp engine/animation_sequence.cpp engine/character_animation.cpp engine/character_model.cpp engine/defined_animation.cpp engine/spritesheet.cpp engine/texture_atlas.cpp engine/font_atlas.cpp engine/sound.cpp engine/loaded_font_spec.cpp engine/rendered_char_spec.cpp sprite/sprite_healthbar.cpp sprite/inventory_coordinate.cpp sprite/inventory.cpp sprite/sprite.cpp sprite/sprite_controller.cpp item/item.cpp item/item_stack.cpp item/bullet.cpp item/consumable.cpp item/gun.cpp item/item_drop.cpp item/sword.cpp attack/attack.cpp attack/punch.cpp attack/sword_swing.cpp attack/fired_bullet.cpp action/sprite_action.cpp action/knockback_action.cpp buff/sprite_buff.cpp util/item_util.cpp game_utils.cpp -o test_sprite_controller -Iengine -Isprite -Iitem -Iattack -Iaction -Ibuff -Iutil -lSDL2 -lSDL2_image -lSDL2_ttf -std=c++11

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "texture_atlas.h"
#include "animation_engine.h"
#include "sprite.h"
#include "inventory.h"
#include "sprite_controller.h"

using namespace std;

bool init();
bool loadMedia();
SDL_Texture* loadTexture(string path);
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
  printf("Created texture atlas\n");
  AnimationEngine anim_eng = AnimationEngine(&t_atlas);
  printf("Created anim engine\n");
  Sprite sprite = Sprite(SpriteType::PLAYER, 100, 100);
  printf("Created sprite\n");
  Inventory inventory = Inventory(&sprite, 0, 0, 5);
  printf("Created inventory\n");
  SpriteController controller = SpriteController(&sprite, &inventory, &anim_eng);
  printf("Created controller\n");

  // inventory.setListener(&controller);
  // printf("Set inventory listener\n");
  // sprite.setListener(&controller);
  // printf("Set sprite listener\n");

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

		// handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN && !e.key.repeat)
			{
				switch( e.key.keysym.sym )
				{
          // change current animation
          case SDLK_w:
            break;
				}
			}
		}
    //
    // civ_anim_player.update(ticks_since_last_frame);
    // pla_anim_player.update(ticks_since_last_frame);

    SDL_Rect screen_background { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderFillRect(gRenderer, &screen_background);

    // civ_anim_player.drawTo(gRenderer, 100, 100);
    // pla_anim_player.drawTo(gRenderer, 200, 100);

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
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
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
