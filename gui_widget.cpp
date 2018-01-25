#include "gui_widget.h"

Widget::Widget(int id)
{
	this->id = id;
}

int Widget::getId()
{
	return id;	
}

SDL_Texture* renderText(SDL_Renderer* renderer, char* text, TTF_Font* font, SDL_Color color)
{
	SDL_Surface* rendered_text_surface = TTF_RenderText_Solid(font, text, color);
	if(rendered_text_surface == NULL)
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
		return NULL;
	}
	else
	{
		SDL_Texture* rendered_text = SDL_CreateTextureFromSurface(renderer, rendered_text_surface);
		if (rendered_text == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", text);	
		}
		SDL_FreeSurface(rendered_text_surface);	
		return rendered_text;
	}
}
