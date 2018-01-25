#include "gui_img_button.h"

ImageButton::ImageButton(int id, SDL_Rect position, TextureAtlas* textureAtlas, FontAtlas* fontAtlas) : Widget(id)
{
	printf("ImageButton created with id %d\n", id);
	this->position = position;
	this->textureAtlas = textureAtlas;
	this->fontAtlas = fontAtlas;
	font = fontAtlas->getFont(MAIN_FONT);
}

void ImageButton::setImage(int textureId)
{
	imageId = textureId; 
}

void ImageButton::setHint(SDL_Renderer* renderer, char* text)
{
	printf("Setting hint of Button with id %d to %s\n", id, text);
	renderedHint = renderText(renderer, text, font, hintColor);
}
void ImageButton::setFont(int fontId)
{
	font = fontAtlas->getFont(fontId);
}

void ImageButton::onReceiveFocus()
{
	focused = true;
	printf("Button %d gaining focus\n", id);
}

void ImageButton::onLoseFocus()
{
	focused = false;	
	printf("Button %d losing focus\n", id);
}

void ImageButton::onClick()
{
	printf("Button clicked!\n");	
	clicked = true;
}

/*void Button::onClickReleased()
{
	clicked = false;	
}*/

bool ImageButton::handleInputEvent(SDL_Event e)
{
	return false;
}

void ImageButton::drawTo(SDL_Renderer* renderer) // TODO: KNOW TIME. THAT WAY IT CAN DECIDE TO SHOW HINT AFTER A CERTAIN AMOUNT OF TIME
{
	if (imageId)
	{
		textureAtlas->draw(renderer, imageId, position.x, position.y);	
	}
	
	// draw hint text
	if (focused)
	{
		hintPosition.x = position.x + position.w;
		hintPosition.y = position.y - 28;
		hintPosition.w = 100;
		hintPosition.h = 28;
		SDL_RenderCopy(renderer, renderedHint, NULL, &hintPosition);
	}
}