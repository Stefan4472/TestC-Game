#ifndef PAUSE_DIALOG_H
#define PAUSE_DIALOG_H

#include <SDL2/SDL.h>
#include "gui_window.h"
#include "gui_button.h"

enum PauseDialogButtons
{
	RESUME_BUTTON,
	EXIT_GAME_BUTTON
};

// window showed when player pauses
class PauseDialog : public Window
{
	public:
		// creates the dialog relative to screen size, initializing elements
		PauseDialog(SDL_Rect position, int closeKeyCode, int screenWidth, int screenHeight, TTF_Font* font, SDL_Color textColor, SDL_Color backgroundColor);
		// handles GUI events (button clicks)
		bool handleGUIEvent(Widget* target);

};

#endif