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
	// adjust widget's position to be relative to this window TODO: ONATTACHED?
	widget->position.x += position.x;
	widget->position.y += position.y;

	widgets.push_back(widget);	
}

bool Window::handleInputEvent(SDL_Event e)
{
	
	// user moved mouse: check if a widget is being hovered over
	if (e.type == SDL_MOUSEMOTION)
	{
		// first check currently-focused widget (if any)
		if (focusedIndex > -1)
		{
			// still focused: return. Else, remove focus
			if (pointInRect(e.motion.x, e.motion.y, widgets[focusedIndex]->position))
			{
				return true;
			}
			else
			{
				printf("Taking focus\n");
				widgets[focusedIndex]->onLoseFocus();
				focusedIndex = -1;	
			}
		}
		// check which widget mouse is hovering over
		for (int i = 0; i < widgets.size(); i++)
		{
			if (pointInRect(e.motion.x, e.motion.y, widgets[i]->position))
			{
				focusedIndex = i;
				widgets[i]->onReceiveFocus();
				printf("Giving Focus\n");
				break;
			}
		}
	}
	// user clicked mouse
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (focusedIndex > -1)
		{
			widgets[focusedIndex]->onClick();	
		}
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
		// handle window-bound keys
		switch (e.key.keysym.sym)
		{
			// deactivate on escape
			case SDLK_ESCAPE:
				active = false;
				return true;
				
			// increment focus on tab or down key
			case SDLK_TAB:
			case SDLK_DOWN:
				if (focusedIndex > -1)
				{
					widgets[focusedIndex]->onLoseFocus();
					focusedIndex = (focusedIndex + 1) % widgets.size();	
					widgets[focusedIndex]->onReceiveFocus();
				}
				else if (widgets.size())
				{
					// set focus to top widget
					focusedIndex = 0;	
					widgets[focusedIndex]->onReceiveFocus();
				}
				return true;
				
			// decrement focus on up key
			case SDLK_UP:
				if (focusedIndex > -1)
				{
					widgets[focusedIndex]->onLoseFocus();
					focusedIndex = (focusedIndex ? focusedIndex - 1 : widgets.size() - 1);
					widgets[focusedIndex]->onReceiveFocus();
				}
				else
				{
					// set focus to top widget
					focusedIndex = 0;	
					widgets[focusedIndex]->onReceiveFocus();
				}
				return true;
				
			// simulate click of focused widget using enter key
			case SDLK_RETURN:
				if (focusedIndex > -1)
				{
					widgets[focusedIndex]->onClick();
				}
				return true;
		}
		// send event to focused
		if (focusedIndex > -1)
		{
			return widgets[focusedIndex]->handleInputEvent(e);	
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
	printf("Done\n");
}
