#ifndef CHARACTER_MODEL_H
#define CHARACTER_MODEL_H

#include "spritesheet_ids.h"
#include "sprite_type.h"

/*
A CharacterModel defines the SpritesheetIds to be played for a Sprite's various
possible actions. It is stateless.
*/

struct CharacterModel
{
  CharacterModel(SpritesheetId (*animations)[5][5]);

  // store Spritesheet Ids indexed by SpriteType x Direction
  // this array should have thenumber of SpriteActionTypes (rows) * number of Directions (cols)
  SpritesheetId (&animations)[5][5];

};

// TODO: THIS WILL GET COMPLETELY DESTROYED IF ANY CHANGE IS MADE TO SPRITE_ACTION_TYPE OR Direction
namespace CharacterModels  // TODO: SEPARATE INTO SEPARATE FILE?
{
  extern CharacterModel NULL_MODEL;  // TODO: MAKE FINAL
  extern CharacterModel CIVILIAN_MODEL;
  extern CharacterModel PLAYER_MODEL;

  extern CharacterModel CHARACTER_MODELS[3];

  // return CharacterModel for the given SpriteType. Indexes into the
  // CHARACTER_MODELS array
  CharacterModel getModel(SpriteType spriteType);
}
#endif
