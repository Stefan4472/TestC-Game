#include "defined_animation.h"

DefinedAnimation::DefinedAnimation(SpriteType spriteType, SpriteActionType actionType,
  ItemType inHandItemType);
{
  this->spriteType = spriteType;
  this->actionType = actionType;
  this->inHandItemType = inHandItemType;
}
