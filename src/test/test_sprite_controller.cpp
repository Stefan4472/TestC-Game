// g++ test/test_sprite_controller.cpp engine/character_model.cpp -o test_sprite_controller -Iengine -Isprite -std=c++11
#include "character_model.h"

int main()
{
  CharacterModels::getModel(SpriteType::CIVILIAN);
}
