#ifndef GUI_WIDGET_H
#define GUI_WIDGET_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

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
	
	public:
		// defines the size and position of button on the screen, RELATIVE TO WINDOW
		SDL_Rect position;
		// widget requires an id
		Widget(int id);
		// returns widget's id
		int getId();
		// attempts to handle a given SDL_Event, and returns whether it was handled
		virtual bool handleInputEvent(SDL_Event e) = 0;
		// gives the widget focus
		virtual void onReceiveFocus() = 0;
		// removes focus
		virtual void onLoseFocus() = 0;
		// handles user clicking on widget
		virtual void onClick() = 0;
		// draws widget in position to given surface
		virtual void drawTo(SDL_Renderer* renderer) = 0;
};

// renders given text using font, size, and color
SDL_Texture* renderText(SDL_Renderer* renderer, const char* text, TTF_Font* font, SDL_Color color);

#endif