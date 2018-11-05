#include "character_animation.h"

CharacterAnimation::CharacterAnimation(Spritesheet* right, Spritesheet* left, Spritesheet* up, Spritesheet* down)
{
  anims[static_cast<int>(Direction::RIGHT)] = right;
  anims[static_cast<int>(Direction::LEFT)] = left;
  anims[static_cast<int>(Direction::UP)] = up;
  anims[static_cast<int>(Direction::DOWN)] = down;
}

bool CharacterAnimation::hasDir(Direction direction)
{
  return anims[static_cast<int>(direction)];
}

Spritesheet* CharacterAnimation::get(Direction direction)
{
  return anims[static_cast<int>(direction)];
}
