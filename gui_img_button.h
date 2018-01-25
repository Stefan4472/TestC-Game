#ifndef GUI_IMAGE_BUTTON_H
#define GUI_IMAGE_BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "texture_atlas.h"
#include "font_atlas.h"
#include "colors.h"
#include "gui_widget.h"
#include "gui_window.h"

// button that can be clicked, and displays an image
class ImageButton: public Widget
{
	// pointer to texture atlas
	TextureAtlas* textureAtlas = NULL;
	// pointer to font atlas
	FontAtlas* fontAtlas = NULL;
	// font used for button text
	TTF_Font* font = NULL;
	// color used for hint text
	SDL_Color hintColor = COLOR_WHITE;
	// rendered hint text
	SDL_Texture* renderedHint = NULL;
	// ID of image to be displayed
	int imageId = NULL;
	// whether button is currently being clicked
	bool clicked = false;
	// position of hint text, if it is shown
	SDL_Rect hintPosition;
	
	public:
		// inits widget with pointer to parent and defined position
		ImageButton(int id, SDL_Rect position, TextureAtlas* textureAtlas, FontAtlas* fontAtlas);
		// sets image to be displayed on button. Image will be sized to the button size
		void setImage(int textureId);
		// sets text for hint displayed over the button when focused
		void setHint(SDL_Renderer* renderer, char* text);
		// sets font for text displayed on button
		void setFont(int fontId);
		void onReceiveFocus();
		void onLoseFocus();
		void onClick();
		// attempts to handle a given KeyEvent, and returns whether it was handled
		bool handleInputEvent(SDL_Event e);
		// draws widget in position to given surface
		void drawTo(SDL_Renderer* renderer);

};

#endif