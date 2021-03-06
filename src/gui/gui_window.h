#ifndef GUI_WINDOW_H
#define GUI_WINDOW_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>
#include "texture_atlas.h"
#include "font_atlas.h"
#include "sound_atlas.h"
#include "colors.h"
#include "gui_widget.h"
#include "gui_button.h"
#include "gui_img_button.h"

// base class for GUI window drawn on the screen
class Window
{
	private:
		// rect defining bounds of the window
		SDL_Rect position;
		// widgets belonging to the window
		std::vector<Widget*> widgets;
		// index of focused widget in widgets list. Will be -1 if none is focused
		int focusedIndex = -1;
		// returns whether the given coordinate is on the given rect
		bool pointInRect(int x, int y, SDL_Rect rect);
	
	public:
		// whether window is on-screen
		bool active;
		// construct window with given width and height (px) centered in screen
		Window(int width, int height, int screenWidth, int screenHeight);
		// adds widget to the window
		void addWidget(Widget* widget);
		// handles user input. Returns false if it was not handled
		bool handleInputEvent(SDL_Event e);
		// draws this window to the given surface
		void drawTo(SDL_Renderer* renderer);
		// free all widgets and window
		~Window();
};

#endif