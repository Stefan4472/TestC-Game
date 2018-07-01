#ifndef CONTROLLER_ADAPTER_H
#define CONTROLLER_ADAPTER_H

#include <SDL2/SDL.h>
#include <unordered_map>

// Interface for mapping key events to in-game commands. This provides support
// for keybinds, and allows checking which commands are currently on.

// available controls in-game. Keys are bound to certain actions.
enum GAME_CONTROLS  // TODO: PUT SOME THOUGHT INTO
{
  CONTROLLER_UP,
  CONTROLLER_DOWN,
  CONTROLLER_LEFT,
  CONTROLLER_RIGHT,
  CONTROLLER_RUN,
  CONTROLLER_USE_ITEM,
  CONTROLLER_DROP_ITEM,
  CONTROLLER_RELOAD,
  CONTROLLER_SHOW_INVENTORY,
  CONTROLLER_CYCLE_INVENTORY_FWD,
  CONTROLLER_CYCLE_INVENTORY_BWD,
  CONTROLLER_ESCAPE,
  CONTROLLER_NUM_CONTROLS
};

// TODO: LOAD FROM FILE, LISTENER FUNCTION SUPPORT
class ControllerAdapter
{
  public:
    // populate mapping with default keyboard keys
    ControllerAdapter();
    // takes the given sdl event and attempts to use it to update control state.
    // returns whether it was handled
    bool handleKeyEvent(SDL_Event e);
    // current state of game controls. TRUE = pressed, FALSE = not pressed
    bool state[CONTROLLER_NUM_CONTROLS];

  private:
    // maps SDL e.key.keysym.sym keys to GAME_CONTROLS. Used to look up key mappings
    std::unordered_map<int, int> keyMap;


};

#endif
