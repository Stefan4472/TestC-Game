#include "pause_dialog.h"

PauseDialog::PauseDialog(SDL_Rect position, int closeKeyCode, int screenWidth, int screenHeight, TTF_Font* font, SDL_Color textColor, SDL_Color backgroundColor) : Window(position, closeKeyCode)
{
	// calculate dimensions of window
	int width = (int) screenWidth * 0.6f;
	int height = (int) screenHeight * 0.8f;
	
	// center window
	position = { (screenWidth - width) / 2, (screenHeight - height) / 2, width, height };  
	
	//	int id, Window* parent, SDL_Rect position, TTF_Font* font, SDL_Color textColor, SDL_Color backgroundColor
	addWidget(new Button(RESUME_BUTTON, this, SDL_Rect{ 0, 0, 100, 50 }, font, textColor, backgroundColor));
	//int btw_width = (int) screenWidth * 
	//Button* resume_btn = new Button(window, SDL_Rect { 50, 50, 50, 50 }*/
}

bool PauseDialog::handleGUIEvent(Widget* target)
{
	printf("Handling event from %d\n", target->getId());
}