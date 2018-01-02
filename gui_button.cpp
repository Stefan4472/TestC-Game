#include "gui_button.h"

Button::Button(Window* parent, SDL_Rect position)
{
	this->parent = parent;
	this->position = position;
}

bool Button::handleEvent(SDL_Event e)
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
	}
	else 
	{
		SDL_FillRect(screenSurface, &position, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));	
	}
}