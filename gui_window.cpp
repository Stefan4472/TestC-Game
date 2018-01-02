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

bool Window::handleKeyEvent(SDL_Event* keyEvent)
{
	return false;	
}

void Window::drawTo(SDL_Surface* screenSurface)
{
	// determine top-left coordinates that will center the window
	dest.x = (screenSurface->w - width) / 2;
	dest.y = (screenSurface->h - height) / 2;
	
	SDL_BlitSurface(baseImg, &src, screenSurface, &dest);
}