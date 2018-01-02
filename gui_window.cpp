#include "gui_window.h"

Window::Window(SDL_Surface* baseImg, int closeKeyCode)
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
	
	this->closeKeyCode = closeKeyCode;
	
	button = new Button(this, SDL_Rect{100, 200, 100, 50});
}

bool Window::isActive()
{
	return active; 
}

void Window::setActive(bool activeState)
{
	active = activeState;
}

bool Window::handleKeyEvent(SDL_Event e)
{
	// key pressed down
	if (e.type == SDL_KEYDOWN) 
	{
		switch( e.key.keysym.sym )
		{ 
			case SDLK_ESCAPE:
				active = false;
				return true;
		}
		if (e.key.keysym.sym == closeKeyCode)
		{
			active = false;
			return true;
		}
	}
	return false;	
}

void Window::drawTo(SDL_Surface* screenSurface)
{
	if (active) 
	{
		// determine top-left coordinates that will center the window
		dest.x = (screenSurface->w - width) / 2;
		dest.y = (screenSurface->h - height) / 2;

		SDL_BlitSurface(baseImg, &src, screenSurface, &dest);
		
		button->drawTo(screenSurface);
	}
}