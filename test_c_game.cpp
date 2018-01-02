#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "gui_window.h"
#include "player_sprite.h"
#include "map.h"

//Screen dimension constants. Actually defined in map.h atm
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;

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

// renderer for the window surface 
SDL_Renderer* gRenderer = NULL;
// colors used in GUI
SDL_Color textColor = {0, 0, 0}, backgroundColor = {0, 0, 0};

// globally used font
TTF_Font *font = NULL;

SDL_Surface *player_idle_img = NULL, *player_mvup_img = NULL, *player_mvdown_img = NULL, *player_mvright_img = NULL, *player_mvleft_img = NULL;
SDL_Surface *brown_brick_tile_img = NULL, *dark_brick_tile_img = NULL, *white_brick_tile_img = NULL, *grass_tile_img = NULL, *water_tile_img = NULL;
SDL_Surface *tree_1_img = NULL, *tree_2_img = NULL, *rock_1_img = NULL, *rock_2_img = NULL, *wooden_fence_left_img = NULL, *wooden_fence_post_img = NULL,\
 *wooden_fence_post_vert_img = NULL;
SDL_Surface *civilian_idle_img = NULL, *civilian_mvup_img = NULL, *civilian_mvdown_img = NULL, *civilian_mvright_img = NULL, *civilian_mvleft_img = NULL;
SDL_Surface *pistol_img = NULL;
SDL_Surface *gui_window_img = NULL;

bool init()
{
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return false;
	}
	
	// set texture filtering to linear
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
		printf( "Warning: Linear texture filtering not enabled!" );
	}
		
	// create window
	gWindow = SDL_CreateWindow( "Stefan's C++ Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( gWindow == NULL )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}
	//Get window surface
	gScreenSurface = SDL_GetWindowSurface( gWindow );
	
	// initialize fonts
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		return false;
	}
	
	// create renderer for window todo: figure out what the issue is (causes segfault)
	/*gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
	if( gRenderer == NULL )
	{
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}
		
	//Initialize renderer color
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	*/
	//Initialize PNG loading
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
	//Loading success flag
	bool success = true;
	
	player_idle_img = loadSurface("graphics/player_idle_spritesheet.png");
	player_mvup_img = loadSurface("graphics/player_mvup_spritesheet.png");
	player_mvdown_img = loadSurface("graphics/player_mvdown_spritesheet.png");
	player_mvright_img = loadSurface("graphics/player_mvright_spritesheet.png");
	player_mvleft_img = loadSurface("graphics/player_mvleft_spritesheet.png");
	
	civilian_idle_img = loadSurface("graphics/civilian_idle_spritesheet.png");
	civilian_mvup_img = loadSurface("graphics/civilian_mvup_spritesheet.png");
	civilian_mvdown_img = loadSurface("graphics/civilian_mvdown_spritesheet.png");
	civilian_mvright_img = loadSurface("graphics/civilian_mvright_spritesheet.png");
	civilian_mvleft_img = loadSurface("graphics/civilian_mvleft_spritesheet.png");
	
	brown_brick_tile_img = loadSurface("graphics/brown_brick_tile.png");
	dark_brick_tile_img = loadSurface("graphics/dark_brick_tile.png");
	white_brick_tile_img = loadSurface("graphics/white_brick_tile_2.png");
	grass_tile_img = loadSurface("graphics/grass_tile.png");
	water_tile_img = loadSurface("graphics/water_tile.png");
	
	tree_1_img = loadSurface("graphics/tree_1.png");
	tree_2_img = loadSurface("graphics/tree_2.png");
	rock_1_img = loadSurface("graphics/rock_1.png");
	rock_2_img = loadSurface("graphics/rock_2.png");
	wooden_fence_left_img = loadSurface("graphics/wooden_fence_left_2.png");
	wooden_fence_post_img = loadSurface("graphics/wooden_fence_post.png");
	wooden_fence_post_vert_img = loadSurface("graphics/wooden_fence_vertical.png");
	
	pistol_img = loadSurface("graphics/pistol_1.png");
	
	gui_window_img = loadSurface("graphics/gui_window.png");
	
	// open the font
	font = TTF_OpenFont( "graphics/lazy.ttf", 28 );
	if(font == NULL)
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		return false;
	}
	return success;
}

void close()
{
	SDL_FreeSurface(player_idle_img);
	SDL_FreeSurface(player_mvup_img);
	SDL_FreeSurface(player_mvdown_img);
	SDL_FreeSurface(player_mvright_img);
	SDL_FreeSurface(player_mvleft_img);
	
	SDL_FreeSurface(civilian_idle_img);
	SDL_FreeSurface(civilian_mvup_img);
	SDL_FreeSurface(civilian_mvdown_img);
	SDL_FreeSurface(civilian_mvright_img);
	SDL_FreeSurface(civilian_mvleft_img);
	
	SDL_FreeSurface(brown_brick_tile_img);
	SDL_FreeSurface(dark_brick_tile_img);
	SDL_FreeSurface(white_brick_tile_img);
	SDL_FreeSurface(grass_tile_img);
	SDL_FreeSurface(water_tile_img);
	
	SDL_FreeSurface(rock_1_img);
	SDL_FreeSurface(rock_2_img);
	SDL_FreeSurface(tree_1_img);
	SDL_FreeSurface(tree_2_img);
	SDL_FreeSurface(wooden_fence_left_img);
	SDL_FreeSurface(wooden_fence_post_img);
	SDL_FreeSurface(wooden_fence_post_vert_img);
	
	SDL_FreeSurface(pistol_img);
	
	SDL_FreeSurface(gui_window_img);
	
	TTF_CloseFont(font);
	font = NULL;

	// destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	
	// destroy renderer
	SDL_DestroyRenderer( gRenderer );
	gRenderer = NULL;

	// quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface( std::string path )
{
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
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
	Map map;
	map.init(&playerSprite, brown_brick_tile_img, dark_brick_tile_img, white_brick_tile_img, grass_tile_img, water_tile_img,
			tree_1_img, tree_2_img, rock_1_img, rock_2_img, wooden_fence_left_img, wooden_fence_post_img, wooden_fence_post_vert_img,
			civilian_idle_img, civilian_mvup_img, civilian_mvdown_img, civilian_mvright_img, civilian_mvleft_img, pistol_img);
	printf("Created map\n");
	// pointer to current Window active on screen
	Window* currWindow = NULL;
	// window showing player inventory
	Window invWindow = Window(gui_window_img, SDLK_e, font, textColor, backgroundColor);
	// window showing pause menu
	Window pauseWindow = Window(gui_window_img, SDLK_p, font, textColor, backgroundColor);
	// window showing quit menu
	Window quitWindow = Window(gui_window_img, -1, font, textColor, backgroundColor);
	
	printf("Created windows\n");
	
	//Main loop flag
	bool quit = false;
	bool paused = false;
	
	Uint32 last_time = SDL_GetTicks();
	Uint32 curr_time;
	Uint32 ticks_since_last_frame;
	int frames = 0;
	
	//Event handler
	SDL_Event e;

	//While application is running
	while( !quit )
	{
		// calculate number of milliseconds since last frame was rendered 
		curr_time = SDL_GetTicks();
		//printf("Curr time is %d\n", curr_time);
		ticks_since_last_frame = curr_time - last_time;
		
		//printf("%u\n", ticks_since_last_frame);
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			// send event to currWindow, if active
			else if (currWindow && currWindow->isActive() && currWindow->handleKeyEvent(e))
			{
				
			}
			// send event to playerSprite, which will handle it in almost all cases.
			else if (playerSprite.handleKeyEvent(e)) 
			{
				
			}
			// handle event on base window level
			else if (e.type == SDL_KEYDOWN)
			{
				switch( e.key.keysym.sym )
				{ 
				// show inventory
					case SDLK_e: 
						invWindow.setActive(true);
						currWindow = &invWindow;
						break;

					// show pause menu
					case SDLK_p: 
						printf("Pausing\n");
						paused = true;
						pauseWindow.setActive(true);
						currWindow = &pauseWindow;
						break;

					// show exit menu
					case SDLK_ESCAPE:
					case SDLK_q: 
						quit = true;
						quitWindow.setActive(true);
						currWindow = &quitWindow;
						break;
				}
			}
		}

		map.update(ticks_since_last_frame);
		
		//printf("Moving playersprite\n");
		playerSprite.move(ticks_since_last_frame);
		
		map.handlePlayer(&playerSprite);
		
		//printf("Updating playersprite\n");
		playerSprite.update(ticks_since_last_frame);
		
		//printf("Drawing Map\n");
		
		//printf("Centering on %d, %d, %d, %d. Sprite at %f, %f\n", playerSprite.hitbox.x, playerSprite.hitbox.y, playerSprite.hitbox.w, playerSprite.hitbox.h, playerSprite.x, playerSprite.y);
		// center map on playerSprite and draw
		map.centerTo(playerSprite.hitbox);
		
		map.drawTerrainTo(gScreenSurface);
		
		//printf("Drawing sprite\n");
		
		playerSprite.drawTo(gScreenSurface, map.viewOffsetX, map.viewOffsetY);
		
		map.drawObjectsTo(gScreenSurface);
		map.drawSpritesTo(gScreenSurface);
		
		// handle current window: draw if active, set to NULL if inactive
		if (currWindow)
		{
			if (currWindow->isActive())
			{
				currWindow->drawTo(gScreenSurface);
			}
			else
			{
				currWindow->setActive(false);
				currWindow = NULL;
			}
		}
		
		// draw changes to window
		SDL_UpdateWindowSurface( gWindow );
		
		//printf("Finished\n");
		// update last_frame_ticks
		last_time = curr_time;
	}

	//Free resources and close SDL
	close();

	return 0;
}