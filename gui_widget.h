#ifndef GUI_WIDGET_H
#define GUI_WIDGET_H

#include <stdio.h>
#include <SDL2/SDL.h>
//#include "gui_window.h"

class Window;

// base class for a GUI element that's put into a Window
class Widget
{
	protected:
		// pointer to Window this widget lives in
		Window* parent = NULL;
		// whether the widget has focus
		bool focused = false;
		// defines the size and position of button on the screen
		SDL_Rect position;
	
	public:
		// attempts to handle a given KeyEvent, and returns whether it was handled
		virtual bool handleEvent(SDL_Event e) = 0;
		// gives the widget focus
		virtual void giveFocus() = 0;
		// draws widget in position to given surface
		virtual void drawTo(SDL_Surface* screenSurface) = 0;
};

#endif