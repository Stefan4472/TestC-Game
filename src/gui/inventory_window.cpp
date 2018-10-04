#include "inventory_window.h"

// return if given point falls within the given rectangle
bool pointInRect(int x, int y, SDL_Rect rect)
{
	return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}

InventoryWindow::InventoryWindow(Inventory* inventory, EngineGUIInterface* engineInterface) // TODO: NEED A SPRITECONTROLLER FOR DROPPED ITEMS
{
  this->inventory = inventory;
  this->engineInterface = engineInterface;

  // 66 pixels per slot (TODO 64, with 2 pix border)
  int inv_width = 64 * (inventory->mainInvCols > inventory->hotbarSize ?
    inventory->mainInvCols : inventory->hotbarSize);
  int inv_height = 64 * (inventory->mainInvRows + 1);
  // TODO: CONSTRAIN TO SCREEN WIDTH/HEIGHT?

  // center window in screen
  windowBounds = SDL_Rect { (engineInterface->getWidth() - inv_width) / 2,
    (engineInterface->getHeight() - inv_height) / 2, inv_width, inv_height };

  // set bounds of main inventory and hotbar
  mainInvBounds = SDL_Rect { windowBounds.x, windowBounds.y,
    inventory->mainInvCols * 64, inventory->mainInvRows * 64 };

  hotbarBounds = SDL_Rect {
    (engineInterface->getWidth() - 64 * inventory->hotbarSize) / 2,
    mainInvBounds.y + mainInvBounds.h,
    64 * inventory->hotbarSize, 64 };

}

void InventoryWindow::handleInputEvent()
{

}

void InventoryWindow::drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas,
  FontAtlas* fontAtlas)
{
  // draw gray window outline
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &windowBounds);


}

void InventoryWindow::forceClose()
{

}

void InventoryWindow::handleMousePressed()
{
  // handle mouse over an inventory slot--"pick up" item
  if (isMouseOverSlot(&selectedSlot)))
  {
    // remove stack from inventory (temporarily)
    selectedStack = inventory->rmvStack(selectedSlot.row, selectedSlot.col, selectedSlot.hotbar);
    slotDragged = true;
  }
}

void InventoryWindow::handleMouseReleased()
{
  // handle mouse over an inventory slot:
  InvCoordinate release_slot(0, 0, false);
  if (isMouseOverSlot(release_slot))
  {
    // add selectedStack to the moused-over slot. "Collect" the displaced slot
    selectedStack = inventory->addStack(selectedStack, release_slot);

    if (selectedStack->isEmpty())
    {
      selectedStack = NULL; // TODO: DELETE?
      slotDragged = false;
    }
    else  // "pick up" displaced stack
    {
      selectedSlot = release_slot;
    }
  }
  // handle mouse in window, but not over a particular slot: return stack to
  // original position
  else if (isMouseInWindow())
  {
    // add selected stack back to original slot
    ItemStack* displaced = inventory->addStack(selectedStack, selectedSlot);
    delete displaced;
    slotDragged = false;
  }
  // handle mouse outside window: drop selected slot
  else
  {
    // TODO: DROP STACK
    printf("Dropping stack\n");
  }
}

bool InventoryWindow::isMouseOverSlot(InvCoordinate& slot)
{
  // handle mouse over main inventory
  if (pointInRect(mouseX, mouseY, mainInvBounds))
  {
    slot->row = (mouseY - mainInvBounds.y) / 64;
    slot->col = (mouseX - mainInvBounds.x) / 64;
    slot->hotbar = false;
    return true;
  }
  else if (pointInRect(mouseX, mouseY, hotbarBounds))
  {
    slot->row = 0;
    slot->col = (mouseX - hotbarBounds.x) / 64;
    slot->hotbar = true;
    return true;
  }
  else
  {
    return false;
  }
}

bool isMouseInWindow()
{
  return mouseX >= windowBounds.x && mouseX < windowBounds.x + windowBounds.w &&
    mouseY >= windowBounds.y && mouseY <= windowBounds.y + windowBounds.h;
}
