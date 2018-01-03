#include "gui_window.h"

Window::Window(SDL_Rect position, int closeKeyCode)
{
	this->position.x = position.x;
	this->position.y = position.y; 
	this->position.w = position.w; 
	this->position.h = position.h; 
	
	this->closeKeyCode = closeKeyCode;
}

bool Window::isActive()
{
	return active; 
}

void Window::setActive(bool activeState)
{
	active = activeState;
}

void Window::addWidget(Widget* widget)
{
	//widget-> todo: make relative to window
	widgets.push_back(widget);	
}

bool Window::handleInputEvent(SDL_Event e)
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
		// draw window background
		SDL_FillRect(screenSurface, &position, SDL_MapRGB(screenSurface->format, 0x47, 0x5C, 0x8D));

		
		for (int i = 0; i < widgets.size(); i++)
		{
			widgets[i]->drawTo(screenSurface);
		} 
	}
}