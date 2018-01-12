#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "gui_widget.h"
#include "gui_window.h"

// button that can be clicked, and displays text
class Button: public Widget
{
	// font used for button text
	TTF_Font* font;
	// color used for text, and background
	SDL_Color textColor, backgroundColor;
	// rendered button text
	SDL_Surface* renderedText;
	
	public:
		// inits widget with pointer to parent and defined position
		Button(int id, Window* parent, SDL_Rect position, char* text, TTF_Font* font, SDL_Color textColor, SDL_Color backgroundColor);
		// attempts to handle a given KeyEvent, and returns whether it was handled
		bool handleInputEvent(SDL_Event e);
		// gives the widget focus
		void giveFocus();
		// draws widget in position to given surface
		void drawTo(SDL_Surface* renderer);

};

#endif