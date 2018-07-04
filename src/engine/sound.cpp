#include "sound.h"

Sound::Sound(Sounds soundId, float x, float y, int radius, Sprite* creator)
{
	this->soundId = soundId;
	this->x = x;
	this->y = y;
  this->radius = radius;
  radiusSquared = radius * radius;
	this->creator = creator;
}
