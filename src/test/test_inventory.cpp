// tests inventory and item/item stack/item drop mechanisms
// g++ test/test_inventory.cpp sprite/inventory.cpp gui/inventory_window.cpp item/item.cpp item/item_stack.cpp item/item_drop.cpp sprite/inventory_coordinate.cpp attack/attack.cpp engine/texture_atlas.cpp action/sprite_action.cpp sprite/sprite.cpp buff/sprite_buff.cpp engine/animation_engine.cpp engine/animation_player.cpp engine/animation_sequence.cpp engine/spritesheet.cpp item/consumable.cpp item/gun.cpp item/bullet.cpp item/sword.cpp util/item_util.cpp engine/sound.cpp attack/fired_bullet.cpp action/knockback_action.cpp attack/sword_swing.cpp attack/punch.cpp engine/font_atlas.cpp engine/rendered_char_spec.cpp engine/loaded_font_spec.cpp -o test_inventory -Iitem -Iattack -Iaction -Isprite -Ibuff -Iengine -Iutil -Igui -I. -lSDL2 -lSDL2_image -lSDL2_ttf -std=c++11

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include "texture_atlas.h"
#include "inventory.h"
#include "inventory_window.h"
#include "item.h"
#include "item_stack.h"
#include "item_drop.h"
#include "item_util.h"
#include "engine_gui_interface.h"

using namespace std;

Inventory* createInventory();
bool init();
bool loadMedia();
SDL_Texture* loadTexture(std::string path);
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* textureAtlasImg = NULL;
TextureAtlas* textureAtlas = NULL;
FontAtlas* fontAtlas = NULL;
InventoryWindow* invWindow = NULL;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

class MockGameEngine : public EngineGUIInterface
{
public:

  bool inventoryOpen = false;

  void run()
  {
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
        // route events to InventoryWindow if open
  			else if (inventoryOpen)
  			{
          invWindow->handleInputEvent(e);
  			}
        // check if user wants to open inventory
        else
        {
          switch( e.key.keysym.sym )
  				{
            case SDLK_e:
              printf("Opening Inventory\n");
              inventoryOpen = true;
              break;
          }
        }
      }

      // black out the screen
      SDL_Rect screen_dim = SDL_Rect { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
      SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
      SDL_RenderFillRect(gRenderer, &screen_dim);

      if (inventoryOpen)
      {
        invWindow->drawTo(gRenderer, textureAtlas, fontAtlas);
      }

      // render screen
  		SDL_RenderPresent(gRenderer);

  		// update last_frame_ticks
  		last_time = curr_time;
  	}
  }

  // inventory closed itself
  void returnControl()
  {
    printf("Returning Control\n");
    inventoryOpen = false;
  }

  void playSound()
  {
    printf("We're supposed to play a sound now\n");
  }

  int getScreenWidth()
  {
    return SCREEN_WIDTH;
  }

  int getScreenHeight()
  {
    return SCREEN_HEIGHT;
  }
};

int main(int argc, char* argv[])
{
  init();
  loadMedia();
  textureAtlas = new TextureAtlas(textureAtlasImg);
  fontAtlas = new FontAtlas();

  // Inventory* inventory = createInventory();
  // char buffer[400];
  // int size = inventory->saveToByteStream(buffer, 400);
  // printf("Save took %d bytes\n", size);
  // FILE* file_handle = fopen("test_inventory_file", "wb");
  // if (file_handle)
  // {
  //   fwrite(buffer, 1, size, file_handle);
  //   fclose(file_handle);
  // }

  printf("Reading inventory from file\n");
  char buffer[400];
  FILE* file_handle = fopen("test_inventory_file", "rb");
  fread(buffer, 1, 400, file_handle);
  Inventory* inventory = Inventory::restoreFromByteStream(buffer, 400);
  printf("Done\n");

  // inventory.swapStacks(0, 0, false, 0, 2, true);
  // inventory.loadInHand();

  MockGameEngine engine;
  invWindow = new InventoryWindow(inventory, &engine);

  engine.run();

  close();
}

Inventory* createInventory()
{
  Inventory* inventory = new Inventory(NULL, 3, 8, 10);
  inventory->addStack(ItemUtil::createStack(ItemType::BREAD_LOAF, 12), InvCoordinate(0, 0, false));
  inventory->addStack(ItemUtil::createStack(ItemType::BREAD_LOAF, 12), InvCoordinate(1, 0, false));
  inventory->addStack(ItemUtil::createStack(ItemType::BEER_MUG, 3), InvCoordinate(2, 0, false));
  inventory->addStack(ItemUtil::createStack(ItemType::SHOTGUN_AMMO, 10), InvCoordinate(0, 3, false));
  inventory->addStack(ItemUtil::createStack(ItemType::PISTOL_AMMO, 36), InvCoordinate(0, 7, false));
  inventory->addStack(ItemUtil::createStack(ItemType::BREAD_LOAF, 5), InvCoordinate(1, 1, false));
  inventory->addStack(ItemUtil::createStack(ItemType::BREAD_LOAF, 8), InvCoordinate(2, 4, false));

  inventory->addStack(ItemUtil::createStack(ItemType::PISTOL, 1), InvCoordinate(0, 0, true));
  inventory->addStack(ItemUtil::createStack(ItemType::PISTOL_AMMO, 32), InvCoordinate(0, 1, true));
  inventory->addStack(ItemUtil::createStack(ItemType::CHICKEN_LEG, 6), InvCoordinate(0, 2, true));
  inventory->addStack(ItemUtil::createStack(ItemType::SWORD, 1), InvCoordinate(2, 0, false));

  return inventory;
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
  gWindow = SDL_CreateWindow("Inventory Test", SDL_WINDOWPOS_UNDEFINED,
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

  TTF_Quit();
  printf("Quit TTF\n");

  SDL_Quit();
	printf("Quit SDL\n");
}
