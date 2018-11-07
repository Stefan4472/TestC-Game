#ifndef DEFINED_ANIMATION_H
#define DEFINED_ANIMATION_H

#include <unordered_map>
#include "sprite_type.h"
#include "sprite_state.h"
#include "item_type.h"

// defines an animation sequence
struct DefinedAnimation
{
  public:
  	SpriteType spriteType;
  	SpriteState spriteState;
  	ItemType inHandItemType;

    DefinedAnimation(SpriteType spriteType, SpriteState spriteState,
      ItemType inHandItemType);

    bool operator==(const DefinedAnimation& other) const
    {
      return spriteType == other.spriteType && spriteState == other.spriteState &&
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
      return static_cast<int>(anim.spriteType) * 500 + 27 * static_cast<int>(anim.spriteState) +
        static_cast<int>(anim.inHandItemType);
    }
  };
}

#endif
