#ifndef CHARACTER_ANIM_H
#define CHARACTER_ANIM_H

#include "spritesheet.h"
#include "direction.h"

/*
Basically a wrapper for storing a spritesheet for each direction.
TODO: BETTER NAME
*/
class CharacterAnimation
{
  private:
    // spritesheets, indexed by direction
    Spritesheet* anims[5] = { NULL, NULL, NULL, NULL, NULL };

  public:
    CharacterAnimation(Spritesheet* right, Spritesheet* left, Spritesheet* up, Spritesheet* down);

    // returns whether a Spritesheet exists for the given direction (i.e., non-NULL)
    bool hasDir(Direction direction);
    // return spritesheet for given direction
    Spritesheet* get(Direction direction);
};
#endif
