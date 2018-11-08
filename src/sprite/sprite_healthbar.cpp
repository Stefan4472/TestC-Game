#include "sprite_healthbar.h"

SpriteHealthBar::SpriteHealthBar(int spriteWidth, int currHp, int fullHp)
{
	outlineRect.w = (int) (spriteWidth * 1.5f);
	outlineRect.h = 10;

	xOffset = - (int) (spriteWidth * 0.25f);
	yOffset = -15;

	this->fullHp = fullHp;
	this->currHp = currHp;

	hpRatio = (float) currHp / fullHp;

	fillRect.w = (int) outlineRect.w * hpRatio;
	fillRect.h = outlineRect.h;

	fillRed = getRed(hpRatio);
	fillGreen = getGreen(hpRatio);
	fillBlue = 0;
}

int SpriteHealthBar::getRed(float hpRatio)
{
	// linear function: 0 at ratio 1, 255 at ratio 0
	return 255 * 0.5f - (hpRatio - 0.5f) * 255;
}

int SpriteHealthBar::getGreen(float hpRatio)
{
	// linear function: 255 at ratio 1, 0 at ratio 0
	return 255 * 0.5f + (hpRatio - 0.5f) * 255;
}

void SpriteHealthBar::changeHealth(int amount)
{
	currHp += amount;
	// floor at zero
	currHp = currHp < 0 ? 0 : currHp;
	hpRatio = (float) currHp / fullHp;

	fillRect.w = (int) outlineRect.w * hpRatio;

	fillRed = getRed(hpRatio);
	fillGreen = getGreen(hpRatio);
}

void SpriteHealthBar::drawTo(SDL_Renderer* renderer, float spriteX, float spriteY)
{
	// draw fill
	SDL_SetRenderDrawColor(renderer, fillRed, fillGreen, fillBlue, SDL_ALPHA_OPAQUE);
	fillRect.x = spriteX + xOffset;
	fillRect.y = spriteY + yOffset;
	SDL_RenderFillRect(renderer, &fillRect);

	// draw outline on top
	SDL_SetRenderDrawColor(renderer, outlineRed, outlineGreen, outlineBlue, SDL_ALPHA_OPAQUE);
	outlineRect.x = spriteX + xOffset;
	outlineRect.y = spriteY + yOffset;
	SDL_RenderDrawRect(renderer, &outlineRect);
}
