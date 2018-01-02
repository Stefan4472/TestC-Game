#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "gui_widget.h"
#include "gui_window.h"

// button that can be clicked, and displays text
class Button: public Widget
{
	public:
		// inits widget with pointer to parent and defined position
		Button(Window* parent, SDL_Rect position);
		// attempts to handle a given KeyEvent, and returns whether it was handled
		bool handleEvent(SDL_Event e);
		// gives the widget focus
		void giveFocus();
		// draws widget in position to given surface
		void drawTo(SDL_Surface* screenSurface);

};

#endif