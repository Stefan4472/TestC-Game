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
	// render button text
	SDL_Surface* rendered_text_surface = TTF_RenderText_Solid(font, text, textColor);
	if(rendered_text_surface == NULL)
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		printf("Rendered to surface\n");
		renderedText = SDL_CreateTextureFromSurface(renderer, rendered_text_surface);
		if (renderedText == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", text);	
		}
		printf("Created Texture\n");
		// free loaded surface (no longer necessary)
		SDL_FreeSurface(rendered_text_surface);	
		printf("Freed surface\n");
	}
}

void Button::setFont(int fontId)
{
	font = fontAtlas->getFont(fontId);
}

void Button::giveFocus()
{
	
}

bool Button::handleInputEvent(SDL_Event e)
{
	return false;
}

void Button::drawTo(SDL_Renderer* renderer)
{
	if (focused)
	{
		SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		SDL_RenderFillRect(renderer, &position);
		SDL_RenderCopy(renderer, renderedText, NULL, &position);
		//SDL_FillRect(renderer, &position, SDL_MapRGB(renderer->format, 0x00, 0x00, 0x00));
		//SDL_BlitSurface(renderedText, NULL, renderer, &position);
	}
	else 
	{
		SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		SDL_RenderFillRect(renderer, &position);
		SDL_RenderCopy(renderer, renderedText, NULL, &position);
		//SDL_FillRect(renderer, &position, SDL_MapRGB(renderer->format, 0xFF, 0xFF, 0xFF));	
		//SDL_BlitSurface(renderedText, NULL, renderer, &position);
	}
}