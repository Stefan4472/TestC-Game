#include "inventory_coordinate.h"

InvCoordinate::InvCoordinate()
{
  row = -1;
  col = -1;
  hotbar = false;
}

InvCoordinate::InvCoordinate(int row, int col, bool hotbar)
{
  this->row = row;
  this->col = col;
  this->hotbar = hotbar;
}
