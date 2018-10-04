#include "inventory_window.h"

// return if given point falls within the given rectangle
bool pointInRect(int x, int y, SDL_Rect rect)
{
	return x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h;
}

InventoryWindow::InventoryWindow(Inventory* inventory, EngineGUIInterface* engineInterface) // TODO: NEED A SPRITECONTROLLER FOR DROPPED ITEMS
{
  printf("Constructing Inventory Window...");
  this->inventory = inventory;
  this->engineInterface = engineInterface;

  // 66 pixels per slot (TODO 64, with 2 pix border)
  int inv_width = 64 * (inventory->mainInvCols > inventory->hotbarSize ?
    inventory->mainInvCols : inventory->hotbarSize);
  int inv_height = 64 * (inventory->mainInvRows + 1);
  // TODO: CONSTRAIN TO SCREEN WIDTH/HEIGHT?

  // center window in screen
  windowBounds = SDL_Rect { (engineInterface->getScreenWidth() - inv_width) / 2,
    (engineInterface->getScreenHeight() - inv_height) / 2, inv_width, inv_height };

  // set bounds of main inventory and hotbar
  mainInvBounds = SDL_Rect {
    (windowBounds.w - inventory->mainInvCols * 64) / 2, windowBounds.y,
    inventory->mainInvCols * 64, inventory->mainInvRows * 64 };

  hotbarBounds = SDL_Rect {
    (engineInterface->getScreenWidth() - 64 * inventory->hotbarSize) / 2,
    mainInvBounds.y + mainInvBounds.h,
    64 * inventory->hotbarSize, 64 };
  printf("done\n");
}

void InventoryWindow::handleInputEvent(SDL_Event e)
{
  switch (e.type)
  {
    // update mouse position
    case SDL_MOUSEMOTION:
      mouseX = e.motion.x;
      mouseY = e.motion.y;
      break;

    // mouse clicked
    case SDL_MOUSEBUTTONDOWN:
      handleMousePressed();
      break;

    // mouse released
    case SDL_MOUSEBUTTONUP:
      handleMouseReleased();
      break;

    // key pressed
    case SDL_KEYDOWN:
      switch (e.key.keysym.sym)
      {
        // return to control on escape or 'e', closing the inventory
        case SDLK_ESCAPE:
        case SDLK_e:
          engineInterface->returnControl();
          break;
      }
  }
}

void InventoryWindow::drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas,
  FontAtlas* fontAtlas)
{
  // printf("Drawing inventory...");
  // draw gray window outline
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &windowBounds);

  // no dragged slot: test for hover
  if (!slotDragged && isMouseOverSlot(&selectedSlot))
  {
    // pick up hovered stack
    ItemStack* hovered = inventory->getStack(selectedSlot);
    string item_name = Item::getName(hovered->itemType);
    string item_description = Item::getDescription(hovered->itemType);
    // printf("Hovering over a stack of %d %s\n", hovered->size(), item_name.c_str());

    // color slot darker
    SDL_Rect slot_bounds = getSlotBounds(selectedSlot);
    SDL_SetRenderDrawColor(renderer, 0xCC, 0xCC, 0xCC, 0xFF);
    SDL_RenderFillRect(renderer, &slot_bounds);
  }

  // draw main inventory slots
  int x = 0, y = mainInvBounds.y;

	// draw main inventory items
	for (int i = 0; i < inventory->mainInvRows; i++)
	{
		x = mainInvBounds.x;
		for (int j = 0; j < inventory->mainInvCols; j++)
		{
			if (inventory->mainInvItems[i][j]->itemType != ItemType::NONE)
			{
				textureAtlas->drawImg(renderer, inventory->mainInvItems[i][j]->itemTexture,
          x, y, false);
			}
			x += 64;
		}
		y += 64;
	}

	x = hotbarBounds.x;

	// draw hotbar items
	for (int j = 0; j < inventory->hotbarSize; j++)
	{
		if (inventory->hotbarItems[j]->itemType != ItemType::NONE)
		{
			textureAtlas->drawImg(renderer, inventory->hotbarItems[j]->itemTexture,
        x, hotbarBounds.y, false);
		}
		x += 64;
	}

  // draw mouse ?

  // draw dragged item, if any
  if (slotDragged)
  {
    // printf("Drawing dragged stack, with texture %d\n", int(selectedStack->itemTexture));
    textureAtlas->drawImg(renderer, selectedStack->itemTexture, mouseX, mouseY, false);
  }

  // TODO: NAME+DESCRIPTION OF HOVERED ITEM, IF ANY

  // draw window bounds
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderDrawRect(renderer, &windowBounds);

  // draw main inventory bounds
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
  SDL_RenderDrawRect(renderer, &hotbarBounds);

  // draw hotbar bounds
  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &mainInvBounds);

  // printf("Done\n");
}

void InventoryWindow::forceClose()
{

}

void InventoryWindow::handleMousePressed()
{
  printf("Handling Mouse Press...");
  // handle mouse over an inventory slot--"pick up" item
  if (isMouseOverSlot(&selectedSlot))
  {
    selectedStack = inventory->getStack(selectedSlot);

    // remove stack from inventory (temporarily) and allow it to be dragged if
    // not empty
    if (selectedStack->itemType != ItemType::NONE)
    {
      printf("Picked up a stack of %d %s\n",selectedStack->size(), Item::getName(selectedStack->itemType).c_str());
      inventory->rmvStack(selectedSlot);
      slotDragged = true;
    }
  }
  printf("Done\n");
}

void InventoryWindow::handleMouseReleased()
{
  printf("Handling mouse release...");
  InvCoordinate release_slot;

  // handle mouse over an inventory slot:
  if (isMouseOverSlot(&release_slot))
  {
    // add selectedStack to the moused-over slot. "Collect" the displaced slot
    selectedStack = inventory->addStack(selectedStack, release_slot);
    printf("Added stack back\n");
    printf("Displaced a stack of %d %s\n",selectedStack->size(), Item::getName(selectedStack->itemType).c_str());
    if (selectedStack->itemType == ItemType::NONE)
    {
      // delete stack and disable dragged item
      delete selectedStack;
      selectedStack = NULL;
      slotDragged = false;
      printf("Ignoring\n");
    }
    else  // "pick up" displaced stack
    {
      selectedSlot = release_slot;
      slotDragged = true;
      printf("Picked up that stack\n");
    }
  }
  // handle mouse in window, but not over a particular slot: return stack to
  // original position
  else if (isMouseInWindow())
  {
    printf("Non-sense click: adding slot back to original position\n");
    // add selected stack back to original slot
    ItemStack* displaced = inventory->addStack(selectedStack, selectedSlot);
    if (displaced->itemType != ItemType::NONE)
    {
      throw runtime_error("Oops, displaced shouldn't have any items in it");
    }
    delete displaced;
    slotDragged = false;
  }
  // handle mouse outside window: drop selected slot
  else
  {
    // TODO: DROP STACK
    printf("Dropping stack\n");
    delete selectedStack;
    selectedStack = NULL;
    slotDragged = false;
  }
  printf("Done\n");
}

SDL_Rect InventoryWindow::getSlotBounds(InvCoordinate slot)
{
  inventory->rangeCheck(slot);

  if (slot.hotbar)
  {
    return SDL_Rect { hotbarBounds.x + 64 * slot.col,
      hotbarBounds.y + 64 * slot.row, 64, 64 };
  }
  else
  {
    return SDL_Rect { mainInvBounds.x + 64 * slot.col,
      mainInvBounds.y + 64 * slot.row, 64, 64 };
  }
}

bool InventoryWindow::isMouseOverSlot(InvCoordinate* slot)
{
  // handle mouse over main inventory
  if (pointInRect(mouseX, mouseY, mainInvBounds))
  {
    // printf("In Main Inv...");
    slot->row = (mouseY - mainInvBounds.y) / 64;
    slot->col = (mouseX - mainInvBounds.x) / 64;
    slot->hotbar = false;
    // printf("Row is %d, col is %d\n", slot->row, slot->col);
    return true;
  }
  else if (pointInRect(mouseX, mouseY, hotbarBounds))
  {
    // printf("In hotbar\n");
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

bool InventoryWindow::isMouseInWindow()
{
  return pointInRect(mouseX, mouseY, windowBounds);
}
