#include "sound.h"

Sound::Sound(SoundType soundType, float x, float y, Sprite* creator)
{
	this->soundType = soundType;
	this->x = x;
	this->y = y;
	this->creator = creator;
}
