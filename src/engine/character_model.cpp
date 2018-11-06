#include "character_model.h"

SpritesheetId NULL_MODEL_ARRAY[5][5] = {
  { SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE },
  { SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE },
  { SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE },
  { SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE },
  { SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE }
};

SpritesheetId CIVILIAN_MODEL_ARRAY[5][5] = {
  { SpritesheetId::NONE, SpritesheetId::CIVILIAN_IDLE_UP, SpritesheetId::CIVILIAN_IDLE_DOWN, SpritesheetId::CIVILIAN_IDLE_LEFT, SpritesheetId::CIVILIAN_IDLE_RIGHT },
  { SpritesheetId::NONE, SpritesheetId::CIVILIAN_WALK_UP, SpritesheetId::CIVILIAN_WALK_DOWN, SpritesheetId::CIVILIAN_WALK_LEFT, SpritesheetId::CIVILIAN_WALK_RIGHT },
  { SpritesheetId::NONE, SpritesheetId::CIVILIAN_RUN_UP, SpritesheetId::CIVILIAN_RUN_DOWN, SpritesheetId::CIVILIAN_RUN_LEFT, SpritesheetId::CIVILIAN_RUN_RIGHT },
  { SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE },
  { SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE }
};

SpritesheetId PLAYER_MODEL_ARRAY[5][5] = {
  { SpritesheetId::NONE, SpritesheetId::PLAYER_IDLE_UP, SpritesheetId::PLAYER_IDLE_DOWN, SpritesheetId::PLAYER_IDLE_LEFT, SpritesheetId::PLAYER_IDLE_RIGHT },
  { SpritesheetId::NONE, SpritesheetId::PLAYER_WALK_UP, SpritesheetId::PLAYER_WALK_DOWN, SpritesheetId::PLAYER_WALK_LEFT, SpritesheetId::PLAYER_WALK_RIGHT },
  { SpritesheetId::NONE, SpritesheetId::PLAYER_RUN_UP, SpritesheetId::PLAYER_RUN_DOWN, SpritesheetId::PLAYER_RUN_LEFT, SpritesheetId::PLAYER_RUN_RIGHT },
  { SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE },
  { SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE, SpritesheetId::NONE }
};

CharacterModel::CharacterModel(SpritesheetId animations[5][5])
{
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      this->animations[i][j] = animations[i][j]; // TODO: IMPROVE
    }
  }
}

CharacterModel CharacterModels::NULL_MODEL = CharacterModel(NULL_MODEL_ARRAY);
CharacterModel CharacterModels::CIVILIAN_MODEL = CharacterModel(CIVILIAN_MODEL_ARRAY);
CharacterModel CharacterModels::PLAYER_MODEL = CharacterModel(PLAYER_MODEL_ARRAY);

CharacterModel CharacterModels::CHARACTER_MODELS[3] = { CharacterModels::NULL_MODEL, CharacterModels::CIVILIAN_MODEL, CharacterModels::PLAYER_MODEL };

CharacterModel CharacterModels::getModel(SpriteType spriteType)
{
  return CharacterModels::CHARACTER_MODELS[static_cast<int>(spriteType)];
}
