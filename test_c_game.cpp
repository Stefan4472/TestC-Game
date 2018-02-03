#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "texture_atlas.h"
#include "sound_atlas.h"
#include "font_atlas.h"
#include "colors.h"
#include "gui_window.h"
#include "pause_dialog.h"
#include "player_sprite.h"
#include "player_sprite_controller.h"
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

// loads individual image and creates a texture out of it
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
// renderer for the window
SDL_Renderer* gRenderer = NULL;

// loaded texture atlas
SDL_Texture *texture_atlas_img = NULL;

bool init()
{
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
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
	
	// create renderer for window 
	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
	if( gRenderer == NULL )
	{
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}
		
	// initialize renderer color
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
	
	// initialize fonts
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		return false;
	}
	
	 // initialize sound mixer
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		return false;
	}
	
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
	texture_atlas_img = loadTexture("graphics/texture_atlas.png");
	if (texture_atlas_img == NULL)
	{
		printf("Failed to load texture image!\n");
		return false;	
	}
	return true;
}

SDL_Texture* loadTexture( std::string path )
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
	SDL_DestroyTexture(texture_atlas_img);
	texture_atlas_img = NULL;
	
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
	TTF_Quit();
	printf("Quit TTF\n");
	IMG_Quit();
	printf("Quit IMG\n");
	SDL_Quit();
	printf("Quit SDL\n");
}

int main( int argc, char* args[] )
{
	printf("Hello from main\n");
	init();
	printf("Initialized\n");
	loadMedia();
	printf("Loaded Media\n");
	TextureAtlas textureAtlas = TextureAtlas(texture_atlas_img);
	printf("Loaded Texture Atlas\n");
	SoundAtlas soundAtlas = SoundAtlas();
	printf("Loaded Sound Atlas\n");
	FontAtlas fontAtlas = FontAtlas();
	printf("Loaded Font Atlas\n");
	PlayerSprite playerSprite = PlayerSprite(100.0f, 140.0f, &textureAtlas, gRenderer, fontAtlas.getFont(MAIN_FONT)); 
	PlayerSpriteController* playerController = new PlayerSpriteController(&playerSprite);
	printf("Created player sprite and controller\n");
	Map map;
	map.init(playerController, &textureAtlas, &soundAtlas);
	printf("Created map\n");
	// pointer to current Window active on screen
	Window* currWindow = NULL;
	// window showing player or sprite inventory
	Window* invWindow = NULL;
	
	// window showing pause menu
	Window* pauseWindow = new Window(100, 300, SCREEN_WIDTH, SCREEN_HEIGHT);;

	Button* playButton = new Button(1, pauseWindow, SDL_Rect { 50, 50, 100, 40 }, &fontAtlas);
	playButton->setText(gRenderer, "Play");
	playButton->setHint(gRenderer, "Press to Play");
	pauseWindow->addWidget(playButton);

	Button* quitButton = new Button(2, pauseWindow, SDL_Rect { 50, 100, 100, 40 }, &fontAtlas);
	quitButton->setText(gRenderer, "Quit");
	quitButton->setHint(gRenderer, "Press to Quit");
	pauseWindow->addWidget(quitButton);

	ImageButton* imgButton = new ImageButton(3, SDL_Rect { 50, 150, 50, 50 }, &textureAtlas, &fontAtlas);
	imgButton->setImage(SWORD_1);
	imgButton->setHint(gRenderer, "This is an Image");
	pauseWindow->addWidget(imgButton);
	
	// window showing quit menu
	//Window* quitWindow = new Window(300, 300, SCREEN_WIDTH, SCREEN_HEIGHT);;
	
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
		frames++;
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
			else if (currWindow && currWindow->active && currWindow->handleInputEvent(e))
			{
				
			}
			// send event to playerSprite, which will handle it in almost all cases.
			else if (playerController->handleKeyEvent(e)) 
			{
				
			}
			// handle event on base window level
			else if (e.type == SDL_KEYDOWN)
			{
				switch( e.key.keysym.sym )
				{ 
					// show player's inventory in window
					case SDLK_e: 
						invWindow = playerController->inventory->getWindow(gRenderer, &textureAtlas, &fontAtlas); // TODO: SHOULDN'T CREATE A NEW WINDOW EVERY TIME
						invWindow->active = true;
						currWindow = invWindow;
						break;

					// show pause menu
					case SDLK_p: 
						printf("Pausing\n");
						paused = true;
						pauseWindow->active = true;
						currWindow = pauseWindow;
						break;

					// show exit menu
					case SDLK_ESCAPE:
						quit = true;
						//quitWindow->active = true;
						//currWindow = quitWindow;
						break;
				}
			}
		}

		map.update(ticks_since_last_frame);
		
		// center map on playerSprite and draw
		map.centerTo(playerController->player->hitbox);
		
		map.drawTo(gRenderer);
		
		// draw heads-up-display
		playerSprite.drawHUD(gRenderer);
		
		// handle current window: draw if active, set to NULL if inactive
		if (currWindow)
		{
			if (currWindow->active)
			{
				currWindow->drawTo(gRenderer);
			}
			else
			{
				currWindow->active = false;
				currWindow = NULL;
			}
		}
		
		if (invWindow && invWindow->active) // currently work-around to draw inventory
		{
			playerController->inventory->drawTo(gRenderer, &textureAtlas);	
		}
		// draw name of in-hand item to screen, if any
		if (playerController->inventory->getInHand()) // TODO: ONLY RENDER WHEN CHANGE OCCURS. Use Item.drawAsInHand()
		{
			//rendered_inhand_name = TTF_RenderText_Solid(font, playerSprite.inventory->getInHand()->getName(), textColor);
			//SDL_BlitSurface(rendered_inhand_name, NULL, gScreenSurface, NULL);
		}

		// update screen
		SDL_RenderPresent(gRenderer);
		
		// update last_frame_ticks
		last_time = curr_time;
	}

	printf("%d frames over %d ms = %d fps\n", frames, last_time, frames * 1000 / last_time);
	delete(invWindow);
	printf("Done1\n");
	delete(pauseWindow);
	//delete(quitWindow);
	printf("Finished Closing Windows\n");
	//Free resources and close SDL
	close();

	return 0;
}