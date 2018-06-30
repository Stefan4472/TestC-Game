#include "menu_creator.h"

#include "gui_window.h"
#include "gui_button.h"

Window* createInventoryWindow(int screenWidth, int screenHeight)
{
	// calculate dimensions of window
	int width = (int) screenWidth * 0.6f;
	int height = (int) screenHeight * 0.8f;
	
	// center window
	SDL_Rect position = { (screenWidth - width) / 2, (screenHeight - height) / 2, width, height };  
	
	Window* window = new Window(position, SDLK_e);
		
		/*		Button(Window* parent, SDL_Rect position, TTF_Font* font, SDL_Color textColor, SDL_Color backgroundColor);
	int btw_width = (int) screenWidth * 
	Button* resume_btn = new Button(window, SDL_Rect { 50, 50, 50, 50 }*/
	return window;
}

Window* createPauseMenu(int screenWidth, int screenHeight)
{
	return new Window(SDL_Rect{ 120, 70, 400, 340 }, SDLK_p);
}

Window* createQuitMenu(int screenWidth, int screenHeight)
{
	return new Window(SDL_Rect{ 120, 70, 400, 340 }, -1);
}