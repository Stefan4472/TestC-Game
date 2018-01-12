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
	// user moved mouse
	if (e.type == SDL_MOUSEMOTION)
	{
		printf("Received mouse motion\n");
	}
	// user clicked mouse
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		printf("user clicked\n");
	}
	// user released mouse
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		printf("user released\n");
	}
	// key pressed down
	else if (e.type == SDL_KEYDOWN) 
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

void Window::drawTo(SDL_Surface* renderer)
{
	if (active) 
	{
		// draw window background
		SDL_FillRect(renderer, &position, SDL_MapRGB(renderer->format, 0x47, 0x5C, 0x8D));

		
		for (int i = 0; i < widgets.size(); i++)
		{
			widgets[i]->drawTo(renderer);
		} 
	}
}

Window::~Window()
{
	printf("Destroying window\n");
	for (int i = 0; i < widgets.size(); i++) 
	{
		printf("Destroying widget with id %d\n", widgets[i]->getId());
		delete(widgets[i]);	
	}
}
