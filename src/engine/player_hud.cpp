#include "player_hud.h"

PlayerHUD::PlayerHUD(int currHealth, int fullHealth, Inventory* inventory, int screenWidth, int screenHeight, TextureAtlas* textureAtlas)
{
	this->currHealth = currHealth;
	this->fullHealth = fullHealth;
	this->inventory = inventory;
	this->textureAtlas = textureAtlas;
	printf("playerhud, atlas is %d\n", textureAtlas);
	
	// apply padding and relative placement of healthbar
	healthBarRect.w = (int) (screenWidth * 0.8f);
	healthBarRect.h = (int) (screenHeight * 0.04f);
	healthBarRect.x = (int) (screenWidth * 0.05f);
	healthBarRect.y = (int) (screenWidth * 0.01f);

	// calculate number of pixels of fill corresponding to one health point
	pxPerHp = healthBarRect.w * 1.0f / fullHealth;
	
	// apply padding and relative placement of healthbar fill
	healthBarFillRect.x = healthBarRect.x + 2;
	healthBarFillRect.y = healthBarRect.y + 2;
	healthBarFillRect.w = currHealth * pxPerHp;
	healthBarFillRect.h = healthBarRect.h - 4;
	
	// position hotbar
	hotbarX = (screenWidth - 320) / 2;
	hotbarY = screenHeight - 40;
	
	// set inHandHighlight
	inHandHighlight.x = hotbarX + inventory->inHandIndex * 32;
	inHandHighlight.y = hotbarY;
}

void PlayerHUD::updateItem(Item* inHand) 
{
	printf("PlayerhUD received update\n");
	// set inHandHighlight to highlight current in-hand item
	inHandHighlight.x = hotbarX + inventory->inHandIndex * 32;
	printf("inhand is %d, highlight.x is %d\n", inventory->inHandIndex, inHandHighlight.x);
}

void PlayerHUD::updateHealth(int newHealth)
{
	// update current health and set fill to reflect it
	currHealth = newHealth;
	healthBarFillRect.w = currHealth * pxPerHp;
}

void PlayerHUD::drawTo(SDL_Renderer* renderer)
{
	// set color to green and draw healthbar fill
	SDL_SetRenderDrawColor(renderer, COLOR_GREEN.r, COLOR_GREEN.g, COLOR_GREEN.b, COLOR_GREEN.a);
	SDL_RenderFillRect(renderer, &healthBarFillRect);
	
	// set color to gray and draw healthbar outline
	SDL_SetRenderDrawColor(renderer, COLOR_GRAY.r, COLOR_GRAY.g, COLOR_GRAY.b, COLOR_GRAY.a);
	SDL_RenderDrawRect(renderer, &healthBarRect);
	
	// draw hotbar and in-hand outline SDL_Renderer* renderer, TextureAtlas* textureAtlas, FontAtlas* fontAtlas, int x, int y TODO: NEED FONTATLAS??
	inventory->drawHotbarTo(renderer, textureAtlas, NULL, hotbarX, hotbarY);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &inHandHighlight);
}
