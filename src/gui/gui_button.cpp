#include "gui_button.h"

Button::Button(int id, Window* parent, SDL_Rect position, FontAtlas* fontAtlas) : Widget(id)
{
	printf("Button created with id %d\n", id);
	this->parent = parent;
	this->position = position;
	this->fontAtlas = fontAtlas;
	font = fontAtlas->getFont(MAIN_FONT);
}

void Button::setText(SDL_Renderer* renderer, char* text) 
{
	printf("Setting text of Button with id %d to %s\n", id, text);
	renderedText = renderText(renderer, text, font, textColor);
}

void Button::setHint(SDL_Renderer* renderer, char* text)
{
	printf("Setting hint of Button with id %d to %s\n", id, text);
	renderedHint = renderText(renderer, text, font, hintColor);
}
void Button::setFont(int fontId)
{
	font = fontAtlas->getFont(fontId);
}

void Button::onReceiveFocus()
{
	focused = true;
	printf("Button %d gaining focus\n", id);
}

void Button::onLoseFocus()
{
	focused = false;	
	printf("Button %d losing focus\n", id);
}

void Button::onClick()
{
	printf("Button clicked!\n");	
	clicked = true;
}

/*void Button::onClickReleased()
{
	clicked = false;	
}*/

bool Button::handleInputEvent(SDL_Event e)
{
	return false;
}

void Button::drawTo(SDL_Renderer* renderer) // TODO: KNOW TIME. THAT WAY IT CAN DECIDE TO SHOW HINT AFTER A CERTAIN AMOUNT OF TIME
{
	if (focused)
	{
		SDL_SetRenderDrawColor(renderer, focusedColor.r, focusedColor.g, focusedColor.b, focusedColor.a);
		SDL_RenderFillRect(renderer, &position);
		SDL_RenderCopy(renderer, renderedText, NULL, &position);
		
		// draw hint text
		hintPosition.x = position.x + position.w;
		hintPosition.y = position.y - 28;
		hintPosition.w = 100;
		hintPosition.h = 28;
		SDL_RenderCopy(renderer, renderedHint, NULL, &hintPosition);
	}
	else 
	{
		SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		SDL_RenderFillRect(renderer, &position);
		SDL_RenderCopy(renderer, renderedText, NULL, &position);
	}
}