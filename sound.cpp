#include "sound.h"

Sound::Sound(int soundId, float x, float y, Sprite* creator)
{
	this->soundId = soundId;
	this->x = x;
	this->y = y;
	this->creator = creator;
}