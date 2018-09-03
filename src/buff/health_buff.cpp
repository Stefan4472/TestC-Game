#include "health_buff.h"

HealthBuff::HealthBuff(int healthChange, int durationMs, AnimationId animationId,
  SoundType startSoundType, SoundType endSoundType)
{
  amountPerMs = healthChange / (float) durationMs;

  if (animationId != AnimationId::NONE)
  {
    spriteAnim = new SimpleAnimation(animationId);
  }

  this->startSoundType = startSoundType;
  this->endSoundType = endSoundType;
}

void HealthBuff::init(Sprite* sprite)
{
  duration = 0;
  elapsedTime = 0;
  startSoundPlayed = false;
}

bool HealthBuff::apply(Sprite* sprite, int ms)
{
  // play start sound if haven't already
  if (!startSoundPlayed && startSoundType != SoundType::NONE)
  {
    lastSound = new Sound(startSoundType, sprite->x, sprite->y, sprite);
  }

  if (elapsedTime + ms > duration && !finished)
	{
    finished = true;
		sprite->addHealth((duration - elapsedTime) * amountPerMs);

    if (endSoundType != SoundType::NONE)
    {
      lastSound = new Sound(endSoundType, sprite->x, sprite->y, sprite);
    }
	}
	else
	{
		sprite->addHealth(ms * amountPerMs);
	}

	elapsedTime += ms;
	return elapsedTime < duration;
}

void getAndClearSounds(vector<Sound*> sounds)
{
  if (lastSound)
  {
    sounds.push_back(lastSound);
    lastSound = NULL;
  }

  // allow deletion when buff is finished and lastSound has been queried
  if (finished)
  {
    destroy = true;
  }
}

void drawToSprite(SDL_Renderer* renderer, TextureAtlas* textureAtlas, Sprite* sprite)
{
  if (spriteAnim)
  {
    spriteAnim->x = sprite->x;
    spriteAnim->y = sprite->y;
    spriteAnim->elapsedTimeMs = elapsedTime;
    textureAtlas->drawAnim(renderer, spriteAnim, sprite->x, sprite->y);
  }
}
