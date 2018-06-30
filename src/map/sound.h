#ifndef SOUND_WRAPPER
#define SOUND_WRAPPER

class Sprite;

// A Sound is created by the Map. It stores the SoundAtlas identifier of the sound created,
// the coordinates on the map the sound originates, and a pointer to the Sprite that created
// the sound.

class Sound
{
	public:
		Sound(int soundId, float x, float y, Sprite* creator);
		int soundId;
		float x, y;
		Sprite* creator;
};
#endif