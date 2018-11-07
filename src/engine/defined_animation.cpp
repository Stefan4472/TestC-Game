#include "defined_animation.h"

DefinedAnimation::DefinedAnimation(SpriteType spriteType, SpriteState spriteState,
  ItemType inHandItemType)
{
  this->spriteType = spriteType;
  this->spriteState = spriteState;
  this->inHandItemType = inHandItemType;
}
