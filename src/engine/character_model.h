#ifndef CHARACTER_MODEL_H
#define CHARACTER_MODEL_H

#include "character_animation.h"
#include "spritesheet_id.h"
#include "sprite_type.h"
#include "sprite_state.h"

/*
A CharacterModel defines the SpritesheetIds to be played for a Sprite's various
possible actions. It is stateless.
*/

class CharacterModel
{
  private:
    // character animations indexed by SpriteState
    CharacterAnimation* animsByState[SpriteStates::NUM_STATES];

  public:
    // init model with CharacterAnimations for each sprite state
    CharacterModel(CharacterAnimation* idleAnim, CharacterAnimation* walkAnim,
      CharacterAnimation* runAnim, CharacterAnimation* useItemAnim,
      CharacterAnimation* dieAnim);

    // get CharacterAnimation for a specified direction
    CharacterAnimation* getAnim(SpriteState spriteState);
};

#endif
