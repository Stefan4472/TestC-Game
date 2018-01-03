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
		// identifier
		int id;
		// pointer to Window this widget lives in
		Window* parent = NULL;
		// whether the widget has focus
		bool focused = false;
		// defines the size and position of button on the screen, RELATIVE TO WINDOW
		SDL_Rect position;
	
	public:
		// widget requires an id
		Widget(int id);
		// returns widget's id
		int getId();
		// attempts to handle a given SDL_Event, and returns whether it was handled
		virtual bool handleInputEvent(SDL_Event e) = 0;
		// gives the widget focus
		virtual void giveFocus() = 0;
		// draws widget in position to given surface
		virtual void drawTo(SDL_Surface* screenSurface) = 0;
};

#endif