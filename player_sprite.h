#ifndef PLAYER_SPRITE_H
#define PLAYER_SPRITE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "texture_atlas.h"
#include "spritesheet.h"
#include "player_hud.h"
#include "action.h"
#include "sprite.h"

// updating: handle input events in queue, call move(), check collisions, handle any collisions, update, draw
class PlayerSprite: public InventoryListener, public Sprite
{
	// renderer 
	SDL_Renderer* renderer = NULL;
	// heads-up-display for the sprite
	PlayerHUD* headsUpDisplay = NULL;
	
	// called when in-hand item changes: updates HUD
	void onInHandItemChanged(Item* newItem);
	
	public:
		PlayerSprite(float xCoord, float yCoord, TextureAtlas* textureAtlas, SDL_Renderer* renderer, TTF_Font* HUDFont); // todo: use initialization list (?)
		// finalizes movement and any other updates to the sprite's state
		void update(int ms);
		// return coordinates of right hand
		SDL_Point getRightHandPosition();
		// draws sprite to the given surface/screen. Subtracting offsets from coordinates results in on-canvas coordinate to draw to
		void drawTo(SDL_Renderer* renderer, int offsetX, int offsetY);
		// draws sprite's head's up display to the screen. Includes healthbar, in-hand item, etc.
		void drawHUD(SDL_Renderer* renderer);
		// given KeyEvent from user, sees whether it is relevant and consumes it. Returns true if it was consumed.
		bool handleKeyEvent(SDL_Event e);
		
		// whether key for interact has been pressed
		bool interactPressed = false;
		// whether the player has pressed key for interaction, and has been handled 
		bool interactHandled = false;
		~PlayerSprite();
};
#endif