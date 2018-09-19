#ifndef ITEM_UTIL_H
#define ITEM_UTIL_H

#include <stdio.h>
#include <stdexcept>
#include "item.h"
#include "item_stack.h"
#include "consumable.h"
#include "gun.h"
#include "bullet.h"
#include "sword.h"

using namespace std;

namespace ItemUtil
{
  // creates an ItemStack of the given ItemType, and the given quantity.
  // the actual size of the stack will be bounded to the item's maximum
  // stack size
  ItemStack* createStack(ItemType itemType, int quantity);
}

#endif
