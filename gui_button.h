#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "font_atlas.h"
#include "colors.h"
#include "gui_widget.h"
#include "gui_window.h"

// button that can be clicked, and displays text
class Button: public Widget
{
	// pointer to font atlas
	FontAtlas* fontAtlas = NULL;
	// font used for button text
	TTF_Font* font = NULL;
	// color used for text, and background
	SDL_Color textColor = COLOR_WHITE, backgroundColor = COLOR_BLACK;
	// rendered button text
	SDL_Texture* renderedText = NULL;
	
	public:
		// inits widget with pointer to parent and defined position
		Button(int id, Window* parent, SDL_Rect position, FontAtlas* fontAtlas);
		// sets text displayed on button
		void setText(SDL_Renderer* renderer, char* text);
		// sets font for text displayed on button
		void setFont(int fontId);
		void giveFocus();
		// attempts to handle a given KeyEvent, and returns whether it was handled
		bool handleInputEvent(SDL_Event e);
		// gives the widget focus
		//void giveFocus();
		// draws widget in position to given surface
		void drawTo(SDL_Renderer* renderer);

};

#endif