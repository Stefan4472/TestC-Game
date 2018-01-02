#include "gui_window.h"

Window::Window(SDL_Surface* baseImg)
{
	this->baseImg = baseImg;
	width = baseImg->w;
	height = baseImg->h;
	
	src.x = 0;
	src.y = 0;
	src.w = width;
	src.h = height;
	
	dest.w = width;
	dest.h = height;
}

void Window::open()
{
	visible = true;	
}

void Window::close()
{
	visible = false;
}

bool Window::handleKeyEvent(SDL_Event e)
{
	// key pressed down
	if (e.type == SDL_KEYDOWN) 
	{
		switch( e.key.keysym.sym )
		{ 
			case SDLK_ESCAPE:
				close();
				return true;

			default:
				return false;
		}
	}
	return false;	
}

void Window::drawTo(SDL_Surface* screenSurface)
{
	if (visible) 
	{
		// determine top-left coordinates that will center the window
		dest.x = (screenSurface->w - width) / 2;
		dest.y = (screenSurface->h - height) / 2;

		SDL_BlitSurface(baseImg, &src, screenSurface, &dest);
	}
}