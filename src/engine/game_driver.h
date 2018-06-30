#ifndef GAME_DRIVER_H
#define GAME_DRIVER_H

#include <SDL2/SDL_mixer.h>
#include "texture_atlas.h"
#include "sound_atlas.h"
#include "sound.h"
#include "item.h"
#include "attack.h"
#include "consumable.h"
#include "sword.h"
#include "pistol.h"
#include "civilian_sprite.h"
#include "player_sprite.h"
#include "sprite_controller.h"
#include "civilian_sprite_controller.h"
#include "player_sprite_controller.h"
#include "follow_path_action.h"
#include "move_in_dir_action.h"

// The GameDriver runs the game, handling input, showing windows, and managing
// the Map, as well as drawing to the screen.

class GameDriver
{
	// pointer to TextureAtlas used for drawing images
	TextureAtlas* textureAtlas = NULL;
	
	// pointer to SoundAtlas used to play sounds
	SoundAtlas* soundAtlas = NULL;
	
	// pointer to player's sprite
	PlayerSpriteController* playerSpriteController = NULL;
	
	// controllers for sprites managed by map
	std::vector<SpriteController*> sprites;
	
	// items generated and managed by map
	std::vector<Item*> items;
	
	// sounds created by sprites, and the map
	std::vector<Sound*> sounds;
	
	// triggers created by sprites that may affect other sprites
	std::vector<Trigger*> triggers;
	
	// handles player request to interact with the map
	void handlePlayerInteract(PlayerSprite* playerSprite);
	
	public:
		GameDriver();
		void run();
};
#endif