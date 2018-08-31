#include "potion_regen_buff.h"

PotionRegenBuff::PotionRegenBuff(ItemType itemType)
{
  switch (itemType)
  {
    case ItemType::POTION_GREEN:  // TODO: CHECK PRECISION
      amountPerMs = GREEN_POTION_HEAL_AMOUNT / GREEN_POTION_HEAL_MS;
      break;
    default:
      throw runtime_error("Invalid ItemType for Potion");
  }
}

void PotionRegenBuff::init(Sprite* sprite)
{
  duration = 0;
  elapsedTime = 0;
  soundPlayed = false;
}

bool PotionRegenBuff::apply(Sprite* sprite, int ms)
{
  if (elapsedTime + ms > duration)
	{
		sprite->addHealth((duration - elapsedTime) * amountPerMs);
	}
	else
	{
		sprite->addHealth(ms * amountPerMs);
	}

	elapsedTime += ms;
	return elapsedTime < duration;
}

void getAndClearSounds(vector<Sounds> sounds)
{
  if (!soundPlayed)
  {
    //sounds.push_back()
  }
}
