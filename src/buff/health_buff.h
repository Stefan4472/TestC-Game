#ifndef HEALTH_BUFF_H
#define HEALTH_BUFF_H

#include <stdexcept>
#include "sprite_buff.h"
#include "item.h"
#include "spritesheet.h"
#include "sound.h"

/*
Changes the sprite's health by the given amount over the given time. Also allows
an animation to be played over the sprite (e.g. a particle effect), and for a
sound to be played at the beginning of the buff, and a different sound to be
played once the buff is completed..
 */
class HealthBuff : public SpriteBuff
{
private:
  // amount of health to regen per ms (calculated in constructor)
	float amountPerMs;
	// time (ms) action lasts, and time it has been going
	int duration = 0, elapsedTime = 0;
	// if buff has finished
	bool finished = false;
  // whether the start sound has been played yet
  bool startSoundPlayed = false;
	// sound to play at start, and then at end
	SoundType startSoundType, endSoundType;

	// last sound created by this buff
	Sound* lastSound = NULL;

public:
  // construct with the given item type. Throws runtime_error if the item type
  // is not a potion.
  HealthBuff(int healthChange, int durationMs, AnimationType animation,
		SoundType startSoundType, SoundType endSoundType);
	// starts tracking time and applying health
  void init(Sprite* sprite);
	// applies health change
  bool apply(Sprite* sprite, int ms);
	// draw buff's effect tot he given sprite
  void drawToSprite(SDL_Renderer* renderer, TextureAtlas* textureAtlas, Sprite* sprite);
	// add lastSound to the vector (if it exists)
	void getAndClearSounds(vector<Sound*> sounds);
};
#endif
