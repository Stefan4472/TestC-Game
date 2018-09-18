#ifndef SOUND_ATLAS
#define SOUND_ATLAS

#include <SDL2/SDL_mixer.h>
#include <random>
#include <assert.h>
#include <stdexcept>
#include "sound_ids.h"
//#include <vector>

// The SoundAtlas manages all loaded sounds and music. Sounds are identified
// by their key in the Sounds enum, and the SoundAtlas loads the files and
// populates an array of Mix_Chunks with the corresponding, loaded audio
// resources upon construction.
class SoundAtlas
{
	// stores loaded sounds corresponding to Sounds enum
	//std::vector<Mix_Chunk*> loadedSounds;
	Mix_Chunk* loadedSounds[int(SoundId::NUM_SOUNDS)]; // TODO: USE VECTOR?

	public:
		static const SoundId FOOTSTEP_GRASS_RUN_SOUNDS[];
		static const int NUM_FOOTSTEP_GRASS_RUN_SOUNDS;
		static const SoundId FOOTSTEP_GRASS_WALK_SOUNDS[];
		static const int NUM_FOOTSTEP_GRASS_WALK_SOUNDS;
		static const SoundId FOOTSTEP_WOOD_WALK_SOUNDS[];
		static const int NUM_FOOTSTEP_WOOD_WALK_SOUNDS;
		static const SoundId GUN_PISTOL_SHOT_SOUNDS[];
		static const int NUM_GUN_PISTOL_SHOT_SOUNDS;
		static const SoundId GUN_PISTOL_SHOT_SILENCED_SOUNDS[];
		static const int NUM_GUN_PISTOL_SHOT_SILENCED_SOUNDS;
		static const SoundId GUN_RIFLE_SHOT_SOUNDS[];
		static const int NUM_GUN_RIFLE_SHOT_SOUNDS;
		static const SoundId GUN_SHOTGUN_SAWED_OFF_SHOT_SOUNDS[]; // TODO: POTENTIALLY RENAME
		static const int NUM_GUN_SHOTGUN_SAWED_OFF_SHOT_SOUNDS;
		static const SoundId GUN_SHOTGUN_SHOT_SOUNDS[];
		static const int NUM_GUN_SHOTGUN_SHOT_SOUNDS;

		SoundAtlas();
		// returns loaded audio for given soundId from the Sounds enum
		Mix_Chunk* getSound(int soundId);
		// plays the given soundId
		void playSound(int soundId);

		// returns a randomly-chosen sound that falls in the given SoundType category
		// basically delegates to the correct get() function, based on soundType
		SoundId getSoundByType(int soundType);

		// the following return a randomly-chosen sound that matches the criteria
		SoundId getFootstepGrassRunSound();
		SoundId getFootstepGrassWalkSound();
		SoundId getFootstepWoodWalkSound();
		SoundId getPistolShotSound();
		SoundId getPistolShotSilencedSound();
		SoundId getRifleShotSound();
		SoundId getShotgunSawedOffShotSound();
		SoundId getShotgunShotSound();

		// frees all loaded audio
		~SoundAtlas();
};

#endif
