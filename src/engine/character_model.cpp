#include "character_model.h"

CharacterModel::CharacterModel(CharacterAnimation* idleAnim, CharacterAnimation* walkAnim,
  CharacterAnimation* runAnim, CharacterAnimation* useItemAnim,
  CharacterAnimation* dieAnim)
{
  animsByState[static_cast<int>(SpriteState::IDLING)] = idleAnim;
  animsByState[static_cast<int>(SpriteState::WALKING)] = walkAnim;
  animsByState[static_cast<int>(SpriteState::RUNNING)] = runAnim;
  animsByState[static_cast<int>(SpriteState::USING_ITEM)] = useItemAnim;
  animsByState[static_cast<int>(SpriteState::DYING)] = dieAnim;
}

CharacterAnimation* CharacterModel::getAnim(SpriteState spriteState)
{
  return animsByState[static_cast<int>(spriteState)];
}
