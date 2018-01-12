#include "healthbar.h"

SpriteHealthBar::SpriteHealthBar(int spriteWidth, int currHp, int fullHp)
{
	outline.w = (int) (spriteWidth * 1.5f);
	outline.h = 10;

	this->fullHp = fullHp;
	this->currHp = currHp;
	
	hpRatio = (float) currHp / fullHp;
	
	fill.w = (int) outline.w * hpRatio;
	fill.h = 10;
	
	colorRed = 0;
	colorGreen = 255;
	colorBlue = 0;
}

void SpriteHealthBar::drawTo(SDL_Renderer* renderer, float spriteX, float spriteY)
{
	SDL_SetRenderDrawColor(renderer, colorRed, colorGreen, colorBlue, SDL_ALPHA_OPAQUE);
	fill.x = spriteX;
	fill.y = spriteY;
	SDL_RenderFillRect(renderer, &fill);
}

