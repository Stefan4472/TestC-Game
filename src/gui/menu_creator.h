#ifndef MENU_CREATOR_H
#define MENU_CREATOR_H

#include "gui_window.h"
#include "gui_button.h"

// builds predefined GUI menus

Window* createInventoryWindow(int screenWidth, int screenHeight);
Window* createPauseMenu(int screenWidth, int screenHeight);
Window* createQuitMenu(int screenWidth, int screenHeight);

#endif