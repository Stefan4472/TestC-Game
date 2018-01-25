#include "gui_window.h"

Window::Window(int width, int height, int screenWidth, int screenHeight)
{
	// set position so window is centered on screen
	this->position.x = (screenWidth - width) / 2;
	this->position.y = (screenHeight - height) / 2; 
	this->position.w = width; 
	this->position.h = height; 
}

void Window::addWidget(Widget* widget)
{
	//widget-> todo: make relative to window
	widgets.push_back(widget);	
}

bool Window::handleInputEvent(SDL_Event e)
{
	
	// user moved mouse: check if a widget is being hovered over
	if (e.type == SDL_MOUSEMOTION)
	{
		printf("Motion\n");
		// first check currently-focused widget (if any)
		if (focused)
		{
			// still focused: return. Else, set to not hovered
			if (pointInRect(e.motion.x, e.motion.y, focused->position))
			{
				return true;
			}
			else
			{
				printf("Taking focus\n");
				//widgets[i]->onStopHover();
				focused = NULL;	
			}
		}
		// check which widget mouse is hovering over
		for (int i = 0; i < widgets.size(); i++)
		{
			if (pointInRect(e.motion.x, e.motion.y, widgets[i]->position))
			{
				focused = widgets[i];
				widgets[i]->giveFocus();
				printf("Giving Focus\n");
				break;
			}
		}
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
	}
	return false;	
}

void Window::drawTo(SDL_Renderer* renderer)
{
	if (active) 
	{
		// draw window background
		SDL_SetRenderDrawColor(renderer, COLOR_BLACK.r, COLOR_BLACK.g, COLOR_BLACK.b, COLOR_BLACK.a);
		SDL_RenderFillRect(renderer, &position);
		
		for (int i = 0; i < widgets.size(); i++)
		{
			widgets[i]->drawTo(renderer);
		} 
	}
}

bool Window::pointInRect(int x, int y, SDL_Rect rect)
{
	return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
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
