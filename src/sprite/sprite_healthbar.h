#ifndef SPRITE_HEALTH_BAR
#define SPRITE_HEALTH_BAR

#include <SDL2/SDL.h>

// A SpriteHealthBar is a visual representation of how much HP a sprite has.
// It is displayed as a rectangle with a certain amount of fill and color.
// A fully-filled, green healthhbar indicates the sprite has full health. As
// the sprite loses health, the color turns to orange, yellow, and then red,
// and is depleted. Calls to loseHealth() and gainHealth() must be made to 
// trigger changes in the display.

// The health bar is positioned relative to a sprite, centered above its head.
// Therefore, the HealthBar must know the width of the sprite it is to portray.

class SpriteHealthBar
{
	private:
		// define the outline of the bar and filled region
		SDL_Rect outlineRect, fillRect;
		// offsets from spriteX, spriteY for drawing outlineRect and fillRect
		float xOffset, yOffset;
		// hp levels when full, and at present moment
		int currHp, fullHp;
		// ratio of currHp to fullHp
		float hpRatio = 0;
		// red, green, blue values of fill color
		int fillRed = 0, fillGreen = 0, fillBlue = 0;
		// red, green, blue values of outline color
		int outlineRed = 105, outlineGreen = 105, outlineBlue = 105;

		// returns red color for given hpRatio
		int getRed(float hpRatio);
		// returns green color for given hpRatio
		int getGreen(float hpRatio);
		
	public:
		SpriteHealthBar(int spriteWidth, int currHp, int fullHp);
		// changes currHealth by the given amount
		void changeHealth(int amount);
		// draws health bar to screen, given sprite's top-left drawing coordinates
		void drawTo(SDL_Renderer* renderer, float spriteX, float spriteY);
};

#endif