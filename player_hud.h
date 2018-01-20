#ifndef PLAYER_HUD
#define PLAYER_HUD

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "item.h"

// The PlayerHUD draws a "heads-up-display" for the player to the screen.
// The HUD includes a healthbar along the top of the screen, as well as 
// rendered text saying the name of the item in-hand (if any).

// The PlayerHUD must be updated via the updateItem() and updateHP() commands.

class PlayerHUD
{
	private:
		// loaded font for displaying item name
		TTF_Font* itemNameFont = NULL;
		// color for displaying item name
		SDL_Color itemNameColor = { 255, 255, 255 };
		// defines position where item name is displayed on the screen
		SDL_Rect itemNamePosition = { 0, 0, 200, 28 };
		// pointer to SDL_Renderer used to render font text
		SDL_Renderer* renderer;
		// texture for rendered text of item name
		SDL_Texture* renderedItemName = NULL;

	public:
		PlayerHUD(SDL_Renderer* renderer, TTF_Font* textFont, Item* inHandItem, int currHealth, int fullHealth);
		// reflects item change. Re-renders text to display
		void updateItem(SDL_Renderer* renderer, Item* newItem);
		// reflects health change. Updates healthbar
		void updateHealth(int newHealth);
		// draws HUD to the given renderer
		void drawTo(SDL_Renderer* renderer);
};
#endif