#include "player_hud.h"

PlayerHUD::PlayerHUD(SDL_Renderer* renderer, TTF_Font* textFont, Item* inHandItem, int currHealth, int fullHealth)
{
	this->renderer = renderer;
	
	itemNameFont = textFont;
	
	if (inHandItem)
	{
		updateItem(renderer, inHandItem);
	}
}

void PlayerHUD::updateItem(SDL_Renderer* renderer, Item* newItem) // TODO: CAUSES VERY STRANGE BEHAVIOR
{
	// free currently rendered name
	/*free(renderedItemName);
	
	// new item exists
	if (newItem)
	{
		SDL_Surface* item_name_surface = TTF_RenderText_Solid(itemNameFont, newItem->getName(), itemNameColor);

		renderedItemName = SDL_CreateTextureFromSurface(renderer, item_name_surface);

		free(item_name_surface);
	}*/
}

void PlayerHUD::updateHealth(int newHealth)
{

}

void PlayerHUD::drawTo(SDL_Renderer* renderer)
{
	// only draw if item name is rendered (there is an item in-hand)
	if (renderedItemName)
	{
		SDL_RenderCopy(renderer, renderedItemName, NULL, &itemNamePosition);
	}
}
