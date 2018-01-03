#include "gui_button.h"

Button::Button(int id, Window* parent, SDL_Rect position, TTF_Font* font, SDL_Color textColor, SDL_Color backgroundColor) : Widget(id)
{
	printf("Button created with id %d\n", id);
	this->parent = parent;
	this->position = position;
	// render button text
	renderedText = TTF_RenderText_Solid(font, "button", textColor);
	if(renderedText == NULL)
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
}

bool Button::handleInputEvent(SDL_Event e)
{
	return false;
}

void Button::giveFocus()
{
	focused = true;
}

void Button::drawTo(SDL_Surface* screenSurface)
{
	if (focused)
	{
		SDL_FillRect(screenSurface, &position, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
		SDL_BlitSurface(renderedText, NULL, screenSurface, &position);
	}
	else 
	{
		SDL_FillRect(screenSurface, &position, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));	
		SDL_BlitSurface(renderedText, NULL, screenSurface, &position);
	}
}