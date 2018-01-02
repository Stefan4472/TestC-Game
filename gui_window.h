#ifndef GUI_WINDOW_H
#define GUI_WINDOW_H

#include <stdio.h>
#include <SDL2/SDL.h>

// GUI window drawn on the screen
class Window
{
	SDL_Surface* baseImg;
	// width and height (px) of the window
	int width, height;
	// rectangles used for drawing
	SDL_Rect src, dest;
	
	public:
		// construct window with image providing the window base
		Window(SDL_Surface* baseImg);
		// attempts to handle given KeyEvent. Returns false if it was not handled
		bool handleKeyEvent(SDL_Event* keyEvent);
		// draws this window to the given surface
		void drawTo(SDL_Surface* screenSurface);
};

#endif