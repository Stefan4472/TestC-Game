#ifndef SOUND_ATLAS
#define SOUND_ATLAS

#include <SDL2/SDL_mixer.h>
//#include <vector>

// The SoundAtlas manages all loaded sounds and music. Sounds are identified
// by their key in the Sounds enum, and the SoundAtlas loads the files and 
// populates an array of Mix_Chunks with the corresponding, loaded audio
// resources upon construction.

enum Sounds
{
	NO_SOUND,
	SOUND_1,
	SOUND_2,
	SOUND_3,
	NUM_SOUNDS
};

class SoundAtlas
{
	// stores loaded sounds corresponding to Sounds enum
	//std::vector<Mix_Chunk*> loadedSounds;
	Mix_Chunk* loadedSounds[NUM_SOUNDS]; // TODO: USE VECTOR?
	
	public:
		SoundAtlas();
		// returns loaded audio for given soundId from the Sounds enum
		Mix_Chunk* getSound(int soundId);
		// frees all loaded audio
		~SoundAtlas();
};

#endif