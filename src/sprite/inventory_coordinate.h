#ifndef INVENTORY_COORDINATE_H
#define INVENTORY_COORDINATE_H

#include <unordered_map>

using namespace std;

/*
Defines the location of an ItemStack in an Inventory. If the item is in
mainStorage, it will have the row and column of the slot the ItemStack is
located, and hotbar will be false. If the item is in the hotbar, it will again
have the row and column of the slot (the row will always be zero), and
hotbar = true. Hashing methods are provided to allow InvCoordinate
objects to be used in unordered_lists.
*/
struct InvCoordinate
{
  public:
    int row, col; // TODO: COULD BE CHAR
    bool hotbar;

    // creates an uninitialized coordinate. Will be invalid (row -1, col -1)
    InvCoordinate();
    InvCoordinate(int x, int y, bool hotbar);

    bool operator==(const InvCoordinate& other) const
    {
      return row == other.row && col == other.col && hotbar == other.hotbar;
    }
};

// TODO: DEFINE IN .CPP FILE?
// define hashing function in std namespace
namespace std
{
  template <>
  struct hash<InvCoordinate>
  {
    size_t operator()(const InvCoordinate& coord) const
    {
      // TODO: TEST, IMPROVE. SHOULD HAVE NO COLLISIONS
      return coord.row + 39 * coord.col + 39 * (coord.hotbar ? 1 : 0);
    }
  };
}

#endif
