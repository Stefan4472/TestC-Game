#ifndef GUI_WINDOW_INTERFACE_H
#define GUI_WINDOW_INTERFACE_H

#include <SDL2/SDL.h>

class GuiWindowInterface
{
  virtual void handleInputEvent(SDL_Event e) = 0;
  // virtual void handleMouseEvent() = 0;
  // virtual void handleControllerEvent() = 0;
  virtual void drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas,
    FontAtlas* fontAtlas);
  virtual void forceClose() = 0;
};

#endif
