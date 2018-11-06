#ifndef CHARACTER_MODEL_H
#define CHARACTER_MODEL_H

#include "spritesheet_id.h"

/*
A CharacterModel defines the SpritesheetIds to be played for a Sprite's various
possible actions. It is stateless.
*/

struct CharacterModel
{
  // store Spritesheet Ids indexed by SpriteType x Direction
  // this array should have thenumber of SpriteActionTypes (rows) * number of Directions (cols)
  SpritesheetId animations[5][5];
};

namespace CharacterModels  // TODO: SEPARATE INTO SEPARATE FILE?
{
  extern CharacterModel NULL_MODEL;  // TODO: MAKE FINAL
  extern CharacterModel CIVILIAN_MODEL;
  extern CharacterModel PLAYER_MODEL;

  extern CharacterModel[3] CHARACTER_MODELS;

  // return CharacterModel for the given SpriteType. Indexes into the
  // CHARACTER_MODELS array
  CharacterModel getModel(SpriteType spriteType);
}
#endif
