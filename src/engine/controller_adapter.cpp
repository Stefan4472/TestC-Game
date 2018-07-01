#include "controller_adapter.h"

ControllerAdapter::ControllerAdapter()
{
  keyMap[SDLK_UP] = CONTROLLER_UP;  // TODO: how to handle mouse clicks?
  keyMap[SDLK_DOWN] = CONTROLLER_DOWN;
  keyMap[SDLK_LEFT] = CONTROLLER_LEFT;
  keyMap[SDLK_RIGHT] = CONTROLLER_RIGHT;
  keyMap[SDLK_SPACE] = CONTROLLER_USE_ITEM;
  keyMap[SDLK_q] = CONTROLLER_DROP_ITEM;
  keyMap[SDLK_r] = CONTROLLER_RELOAD;
  keyMap[SDLK_e] = CONTROLLER_SHOW_INVENTORY;
  keyMap[SDLK_i] = CONTROLLER_CYCLE_INVENTORY_FWD;
  keyMap[SDLK_o] = CONTROLLER_CYCLE_INVENTORY_BWD;
  keyMap[SDLK_ESCAPE] = CONTROLLER_ESCAPE;
}

bool ControllerAdapter::handleKeyEvent(SDL_Event e)
{

  if ((e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) && !e.key.repeat)
  {
    std::unordered_map<int, int>::const_iterator got = keyMap.find(e.key.keysym.sym);
    if (got == keyMap.end())
    {
      printf("No mapping available\n");
      return false;
    }
    else
    {
      printf("Mapped to %d\n", got->second);
      state[got->second] = !state[got->second];
      printf("state is %s\n", state[got->second] ? "ON" : "OFF");
      return true;
    }
  }
  return false;  // TODO: MAKE ACTUALLY USEFUL
}
