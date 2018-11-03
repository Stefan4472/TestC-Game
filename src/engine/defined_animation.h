#ifndef DEFINED_ANIMATION_H
#define DEFINED_ANIMATION_H

#include "sprite_type.h"
#include "sprite_action_type.h"
#include "item_type.h"

// defines an animation sequence
struct DefinedAnimation
{
  public:
  	SpriteType spriteType;
  	SpriteActionType actionType;
  	ItemType inHandItemType;

    DefinedAnimation(SpriteType spriteType, SpriteActionType actionType,
      ItemType inHandItemType);

    bool operator==(const DefinedAnimation& other) const
    {
      return spriteType == other.spriteType && actionType == other.actionType &&
        inHandItemType == other.inHandItemType;
    }
};

// TODO: DEFINE IN CPP FILE
// define hashing function in std namespace
namespace std
{
  template <>
  struct hash<DefinedAnimation>
  {
    size_t operator()(const DefinedAnimation& anim) const
    {
      return static_cast<int>(anim.spriteType) * 500 + 27 * static_cast<int>(anim.actionType) +
        static_cast<int>(anim.inHandItemType);
    }
  };
}

#endif
