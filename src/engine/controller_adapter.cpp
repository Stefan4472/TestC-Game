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

  for (int i = 0; i < sizeof(state); i++)
  {
    state[i] = false;
  }
}

void ControllerAdapter::setListener(ControllerListener* listener)
{
  this->listener = listener;
}

bool ControllerAdapter::handleKeyEvent(SDL_Event e)
{
  if ((e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) && !e.key.repeat)
  {
    std::unordered_map<int, GAME_CONTROLS>::const_iterator got = keyMap.find(e.key.keysym.sym);
    if (got == keyMap.end())
    {
      return false;
    }
    else
    {
      printf("Got event for control %d, whose state is %d\n", got->second, state[got->second]);
      state[got->second] = !state[got->second];
      if (listener)
      {
        if (state[got->second])
        {
          listener->onControlStart(got->second);
        }
        else
        {
          listener->onControlEnd(got->second);
        }
      }
      return true;
    }
  }
  return false;  // TODO: MAKE ACTUALLY USEFUL
}
