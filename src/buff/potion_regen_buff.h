#ifndef POTION_REGEN_BUFF_H
#define POTION_REGEN_BUFF_H

#include <stdexcept>
#include "sprite_buff.h"
#include "item.h"
#include "spritesheet.h"

// Health regen buff given by a potion item. Amount of HP regen and duration
// depends on potion type. TODO: SUPPORT MORE POTION TYPES
class PotionRegenBuff : public SpriteBuff
{
private:
  // amount of health to regen per ms (calculated in constructor)
	float amountPerMs;
	// time (ms) action lasts, and time it has been going
	int duration = 0, elapsedTime = 0;
  // whether the health regen sound has been played yet
  bool soundPlayed = false;

  const int GREEN_POTION_HEAL_MS = 300;
  const float GREEN_POTION_HEAL_AMOUNT = 20;

public:
  // construct with the given item type. Throws runtime_error if the item type
  // is not a potion.
  PotionRegenBuff(ItemType item);

  void init(Sprite* sprite);

  bool apply(Sprite* sprite, int ms);

  void drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas, Sprite* sprite);
  void getAndClearSounds(vector<Sounds> sounds);
};
#endif
