#include "inventory_coordinate.h"

InvCoordinate::InvCoordinate(int row, int col, bool hotbar)
{
  this->row = row;
  this->col = col;
  this->hotbar = hotbar;
}
