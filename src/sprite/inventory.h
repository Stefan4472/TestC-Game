#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <vector>
#include <unordered_map>
#include <list>
#include <stdexcept>
#include "constants.h"
#include "texture_atlas.h"
#include "font_atlas.h"
#include "inventory_coordinate.h"
// #include "gui_window.h"
// #include "gui_img_button.h"
#include "item.h"
#include "item_stack.h"
#include "sprite.h"
#include "punch.h"

using namespace std;

// TODO: UPDATE
// An inventory manages the Items a Sprite has and can use. It also manages the usage and effects of
// those items.
// Items are stored as pointers in a vector, so memory deallocation should not be done to live items.
// An inventory has an Item "in-hand", which can be used at any time. Items are referred to by
// their index in the vector.
// The Inventory stores the Actins, Buffs, and Attacks created by using the item in hand. These must
// be managed properly, as they will be overridden once the next item is used. They are accessed via
// the getAction(), getBuff(), and getAttack() methods.
// Example usage: Call inventory->useInHand(), then store inventory->getAction(), getBuff(), getAttack().
// Store those which are non-null.

// An InventoryListener is an interface that allows callbacks from an Inventory. The implementing object
// must register itself via setInventoryListener().
class InventoryListener
{
	public:
		virtual void onInHandItemChanged(Item* newItem) = 0;
};

class Inventory // TODO: SEPARATE CLASS FOR NON-SPRITE INVENTORIES
{
	private:
		// sprite to which this Inventory belongs
		Sprite* owner = NULL;

		// size of hotbar
		int hotbarSize;
		vector<ItemStack*> hotbarItems;

		// index in hotbar the owner has selected, or "in-hand"
		int inHandIndex;

		// rows and columns of main inventory (everything besides hotbar),
		// and total size (rows * cols)
		int mainInvRows, mainInvCols, mainInvSize;
		vector<vector<ItemStack*>> mainInvItems;

		// currently empty hotbar slots in the hotbar and main inventory TODO: ORDER FROM TOP TO BOTTOM?
		list<InvCoordinate> emptyHotbarSlots;
		list<InvCoordinate> emptyMainSlots;

		// maps an ItemType to a list of locations of stacks of the ItemType.
		// hotbar and main inventory mappings are stored separately
		unordered_map<ItemType, list<InvCoordinate>> hotbarMappings;
		unordered_map<ItemType, list<InvCoordinate>> mainMappings;

		// stored Action, Buff, and Attack (if any) from last-used Item
		SpriteAction* resultingAction = NULL;
		SpriteAction* resultingBuff = NULL;
		Attack* resultingAttack = NULL;
		// TODO: STORE CREATED SOUNDS

		// pointer to listener, if any
		InventoryListener* inventoryListener = NULL;

		// searches for stack of items with given id. May return Null
		InvCoordinate findItemSlot(ItemType, InvCoordinate& slot);
		// searches inventory for an ItemStack that can accept the given item, if any (may be NULL)
		InvCoordinate findEmptySlot(Item* item);

	public:
		// creates an inventory with the given number of rows and columns and a
		// hotbar of the given size for the owner. Item usage will be attributed to
		// the owner. Optionally takes an InventoryListener
		Inventory(Sprite* owner, int rows, int cols, int hotbarSize, InventoryListener* listener=NULL);

		// sets listener function for in-hand item change
		void setListener(InventoryListener* listener);

		// add the given stack to the specified inventory slot. Returns the
		// displaced ItemStack, if any
		ItemStack* addStack(ItemStack* stack, int row, int col, bool hotbar);
		// attempts to add the stack somewhere in the inventory, prioritizing the
		// hotbar. Returns whether this was possible. May take items from the given
		// stack to fill stacks currently in inventory
		bool autoAddStack(ItemStack* stack);
		// removes and returns the stack at the given slot. Might not contain an item
		ItemStack* rmvStack(int row, int col, bool hotbar);
		// swaps the stacks at the two given slots
		void swapStacks(int row, int col, bool hotbar, int swapRow, int swapCol, bool swapHotbar);

		// returns pointer to the Item that's currently in hand. Null if empty
		Item* getInHand();  // TODO: IS THIS USED? SHOULDN'T IT RETURN AN ITEM STACK?

		// handles all logic for using whatever item is currently in hand. Should be
		// followed up witH getAction(), getBuff(), and getAttack(), one or more of
		// which may be NULl TODO: HANDLING CONSUMABLES? PUNCHING IF IN-HAND IS EMPTY?
		void useInHand();
		// attempts to load/reload whatever item is in hand with the correct items
		// from inventory (e.g., will reload a gun with bullets from inventory).
		// Will only do something if that item can be reloaded, and the correct
		// ammunition is in inventory.
		void loadInHand();
		// removes and returns the ItemStack currently selected in the hotbar
		ItemStack* dropInHand();

		// retrieve *AND CONSUME* Action, Buff, and/or Attack that may have been
		// created by last-used item. CAN BE NULL
		SpriteAction* getAction();
		SpriteAction* getBuff();
		Attack* getAttack();

		// sets in hand item to the proceeding one in inventory, wrapping around.
		// Doesn't do anything if hotbarSize is less than two
		void cycleInHandFwd();
		// sets in hand item to the preceeding one in inventory, wrapping around.
		// Doesn't do anything if hotbarSize is less than two
		void cycleInHandBck();

		// draws hotbar items to the screen at x, y
		void drawHotbarTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas, FontAtlas* fontAtlas, int x, int y);
		// simple drawing for debugging
		void drawDebugTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas,
			FontAtlas* fontAtlas);
		// opens a Window with inventory displayed
		// Window* getWindow(SDL_Renderer* renderer, TextureAtlas* textureAtlas, FontAtlas* fontAtlas);
};
#endif
