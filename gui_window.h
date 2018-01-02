#ifndef GUI_WINDOW_H
#define GUI_WINDOW_H

#include <stdio.h>
#include <vector>
#include <SDL2/SDL.h>
#include "gui_widget.h"
#include "gui_button.h"

// GUI window drawn on the screen
class Window
{
	// rect defining bounds of the window
	SDL_Rect position;
	// whether window is active and can be drawn to screen
	bool active = false;
	// key code of key that can close the window, besides ESC
	int closeKeyCode = -1;
	// widgets belonging to the window
	std::vector<Widget*> widgets;
	// widget in focus (NULL if none)
	Widget *focused = NULL;
	
	
	public:
		// construct window filling position rect with image providing the window base
		Window(SDL_Rect position, int closeKeyCode);
		// whether window is currently active
		bool isActive();
		// set active state of window
		void setActive(bool activeState);
		// adds widget to the window
		void addWidget(Widget* widget);
		// attempts to handle given KeyEvent. Returns false if it was not handled
		bool handleKeyEvent(SDL_Event e);
		// draws this window to the given surface
		void drawTo(SDL_Surface* screenSurface);
};

#endif