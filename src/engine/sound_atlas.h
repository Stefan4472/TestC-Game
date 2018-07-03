#ifndef SOUND_ATLAS
#define SOUND_ATLAS

#include <SDL2/SDL_mixer.h>
#include <assert.h>
//#include <vector>

// The SoundAtlas manages all loaded sounds and music. Sounds are identified
// by their key in the Sounds enum, and the SoundAtlas loads the files and
// populates an array of Mix_Chunks with the corresponding, loaded audio
// resources upon construction.

enum Sounds
{
	NO_SOUND,
	FOOTSTEP_GRASS_RUN_01,
	FOOTSTEP_GRASS_RUN_02,
	FOOTSTEP_GRASS_RUN_03,
	FOOTSTEP_GRASS_RUN_04,
	FOOTSTEP_GRASS_RUN_05,
	FOOTSTEP_GRASS_WALK_01,
	FOOTSTEP_GRASS_WALK_02,
	FOOTSTEP_GRASS_WALK_03,
	FOOTSTEP_GRASS_WALK_04,
	FOOTSTEP_GRASS_WALK_05,
	FOOTSTEP_GRAVEL_RUN_01,
	FOOTSTEP_GRAVEL_RUN_02,
	FOOTSTEP_GRAVEL_RUN_03,
	FOOTSTEP_GRAVEL_RUN_04,
	FOOTSTEP_GRAVEL_RUN_05,
	FOOTSTEP_WOOD_WALK_01,
	FOOTSTEP_WOOD_WALK_02,
	FOOTSTEP_WOOD_WALK_03,
	FOOTSTEP_WOOD_WALK_04,
	FOOTSTEP_WOOD_WALK_05,
	GUN_PISTOL_SHOT_01,
	GUN_PISTOL_SHOT_02,
	GUN_PISTOL_SHOT_03,
	GUN_PISTOL_SHOT_04,
	GUN_PISTOL_SHOT_05,
	GUN_PISTOL_SHOT_SILENCED_01,
	GUN_PISTOL_SHOT_SILENCED_02,
	GUN_PISTOL_SHOT_SILENCED_03,
	GUN_PISTOL_SHOT_SILENCED_04,
	GUN_PISTOL_SHOT_SILENCED_05,
	GUN_RIFLE_SHOT_01,
	GUN_RIFLE_SHOT_02,
	GUN_RIFLE_SHOT_03,
	GUN_RIFLE_SHOT_04,
	GUN_SHOTGUN_SAWED_OFF_SHOT_01,
	GUN_SHOTGUN_SAWED_OFF_SHOT_02,
	GUN_SHOTGUN_SAWED_OFF_SHOT_03,
	GUN_SHOTGUN_SAWED_OFF_SHOT_04,
	GUN_SHOTGUN_SHOT_01,
	GUN_SHOTGUN_SHOT_02,
	GUN_SHOTGUN_SHOT_03,
	GUN_SHOTGUN_SHOT_04,
	NUM_SOUNDS
};

class SoundAtlas
{
	// stores loaded sounds corresponding to Sounds enum
	//std::vector<Mix_Chunk*> loadedSounds;
	Mix_Chunk* loadedSounds[NUM_SOUNDS]; // TODO: USE VECTOR?

	public:
		//static const Sounds[] FOOTSTEP_GRASS_RUN_SOUNDS;
		SoundAtlas();
		// returns loaded audio for given soundId from the Sounds enum
		Mix_Chunk* getSound(int soundId);
		// plays the given soundId
		void playSound(int soundId);
		// frees all loaded audio
		~SoundAtlas();
};

#endif
