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
	// whether window is active and can be drawn to screen
	bool active = false;
	// key code of key that can close the window, besides ESC
	int closeKeyCode = -1;
	
	public:
		// construct window with image providing the window base
		Window(SDL_Surface* baseImg, int closeKeyCode);
		// whether window is currently active
		bool isActive();
		// set active state of window
		void setActive(bool activeState);
		// attempts to handle given KeyEvent. Returns false if it was not handled
		bool handleKeyEvent(SDL_Event e);
		// draws this window to the given surface
		void drawTo(SDL_Surface* screenSurface);
};

#endif