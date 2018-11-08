#include "character_animation.h"

CharacterAnimation::CharacterAnimation(Spritesheet* right, Spritesheet* left, Spritesheet* up, Spritesheet* down)
{
  cout << "Creating CharacterAnimation" << endl;
  anims[static_cast<int>(Direction::NONE)] = NULL;
  anims[static_cast<int>(Direction::RIGHT)] = right;
  anims[static_cast<int>(Direction::LEFT)] = left;
  anims[static_cast<int>(Direction::UP)] = up;
  anims[static_cast<int>(Direction::DOWN)] = down;

  for (int i = 0; i < 5; i++)
  {
    cout << anims[i] << endl;
  }
}

bool CharacterAnimation::hasDir(Direction direction)
{
  cout << "hello from hasDir with direction/index " << static_cast<int>(direction) << endl;
  cout << anims[int(Direction::NONE)] << endl;
  for (int i = 0; i < 5; i++)
  {
    cout << "i is " << i << endl;
    if (anims[0])
    {
      cout << "yo";
    }
    else
    {
      cout << "no";
    }
    cout << anims[i] << " ";
  }
  cout << "done " << endl;
  return anims[static_cast<int>(direction)];
}

Spritesheet* CharacterAnimation::get(Direction direction)
{
  return anims[static_cast<int>(direction)];
}
