#ifndef INVENTORY_GUI_H
#define INVENTORY_GUI_H

#include <stdexcept>
#include "gui_window_interface.h"
#include "engine_gui_interface.h"
#include "texture_atlas.h"
#include "font_atlas.h"
#include "inventory.h"
#include "item_stack.h"
#include "item_drop.h"
#include "inventory_coordinate.h"

class SpriteController;

using namespace std;

class InventoryWindow : public GuiWindowInterface
{
  private:
    // inventory being shown
    Inventory* inventory = NULL;
    // interface to game engine
    EngineGUIInterface* engineInterface = NULL;
    // rect defining size and position of the window
    SDL_Rect windowBounds;
    // rect defining size and position of main inventory and hotbar, respectively
    SDL_Rect mainInvBounds;
    SDL_Rect hotbarBounds;

    // TODO: BOOL MOUSE_MOVED

    // mouse coordinates (top-left)
    int mouseX, mouseY;
    // is mouse clicked currently?
    bool slotDragged = false;
    // coordinate of the slot that's being dragged+dropped. Garbage unless slotDragged is true
    InvCoordinate selectedSlot;
    // stack that's being dragged+dropped
    ItemStack* selectedStack = NULL;

    //InvCoordinate resolveCoordinate

    void handleMousePressed();

    SDL_Rect getSlotBounds(InvCoordinate slot);

    // returns if mouse coordinates are hovering over a slot. If so, sets the
    // given InvCoordinate to that slot
    bool isMouseOverSlot(InvCoordinate* slot);
    // returns if the mouse is within the bounds of the inventory window
    bool isMouseInWindow();


  public:
    InventoryWindow(Inventory* inventory, EngineGUIInterface* engineInterface);  // TODO: NEED A SPRITECONTROLLER FOR DROPPED ITEMS
    void handleInputEvent(SDL_Event e);
    void drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas,
      FontAtlas* fontAtlas);
    void forceClose();
};

#endif
