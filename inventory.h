#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <vector>
#include "constants.h"
#include "texture_atlas.h"
#include "font_atlas.h"
#include "gui_window.h"
#include "gui_img_button.h"
#include "item.h"
#include "item_stack.h"
#include "sprite.h"
#include "punch.h"

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

		// size of hotbar (items at ready selection)
		int hotbarSize = 0;
		std::vector<ItemStack*> hotbar;
		//std::vector<int> emptyHotbarSlots;
		// size of inventory (rest of items)
		int inventorySize = 10;
		std::vector<ItemStack*> inventory;
		//std::vector<int> emptyInventorySlots;

		// number of items that'll fit in the inventory
		int capacity = 10;
		// vector of pointers to items in storage
		std::vector<Item*> items;
		// stored Action, Buff, and Attack (if any) from last-used Item
		Action* resultingAction = NULL;
		Action* resultingBuff = NULL;
		Attack* resultingAttack = NULL;
		// pointer to listener, if any
		InventoryListener* inventoryListener = NULL;
		// searches for stack of items with given id. May return Null
		ItemStack* findItems(int id);
	
	public:
		// creates enough space for the given number of items. Item uses are attributed to given owner
		Inventory(Sprite* owner, int capacity);
		// attempts to add an item to inventory. Returns false if inventory is full
		bool addItem(Item* item);
		// index of Item that's currently in hand
		int inHandIndex = -1;
		// returns pointer to the Item that's currently in hand. Null if empty 
		Item* getInHand();
		// handles all logic for using whatever item is currently in hand. Should be followed up with           TODO: HOW TO HANDLE CONSUMMABLES?
		// getAction(), getBuff(), and getAttack(), one or more of which may be NULL. Takes the sprite's
		// current hand position, and direction facing, which is used for positional effects.
		void useInHand(SDL_Point handPos, int useDir); 
		// attempts to load whatever item is in hand. Will only do something if that item can be reloaded, and 
		// the correct ammunition is in inventory.
		void loadInHand();
		// retrieve *AND CONSUME* Action, Buff, and/or Attack that may have been created by last-used item. 
		Action* getAction();
		Action* getBuff();
		Attack* getAttack();
		// sets in hand item to the proceeding one in inventory. Doesn't do anything if vector has only 1 element
		void cycleInHandFwd();
		// sets in hand item to the preceeding one in inventory. Doesn't do anything if vector has only 1 element
		void cycleInHandBck();
		// removes and returns in-hand item, if it exists. Automatically cycles forward
		Item* removeInHand();
		// sets listener function for in-hand item change
		void setListener(InventoryListener* listener);
		// draws hotbar items to the screen at x, y
		void drawHotbarTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas, FontAtlas* fontAtlas, int x, int y);
		// opens a Window with inventory displayed
		Window* getWindow(SDL_Renderer* renderer, TextureAtlas* textureAtlas, FontAtlas* fontAtlas);
};
#endif