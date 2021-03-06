#include "sound_atlas.h"

const SoundId SoundAtlas::FOOTSTEP_GRASS_RUN_SOUNDS[] = {
	FOOTSTEP_GRASS_RUN_01, FOOTSTEP_GRASS_RUN_02, FOOTSTEP_GRASS_RUN_03,
	FOOTSTEP_GRASS_RUN_04, FOOTSTEP_GRASS_RUN_05 };
const int SoundAtlas::NUM_FOOTSTEP_GRASS_RUN_SOUNDS =
	sizeof(SoundAtlas::FOOTSTEP_GRASS_RUN_SOUNDS) / sizeof(Sounds);

const SoundId SoundAtlas::FOOTSTEP_GRASS_WALK_SOUNDS[] = {
	FOOTSTEP_GRAVEL_RUN_01, FOOTSTEP_GRAVEL_RUN_02, FOOTSTEP_GRAVEL_RUN_03,
	FOOTSTEP_GRAVEL_RUN_04, FOOTSTEP_GRAVEL_RUN_05 };
const int SoundAtlas::NUM_FOOTSTEP_GRASS_WALK_SOUNDS =
	sizeof(SoundAtlas::FOOTSTEP_GRASS_WALK_SOUNDS) / sizeof(Sounds);

const SoundId SoundAtlas::FOOTSTEP_WOOD_WALK_SOUNDS[] = {
	FOOTSTEP_WOOD_WALK_01, FOOTSTEP_WOOD_WALK_02, FOOTSTEP_WOOD_WALK_03,
	FOOTSTEP_WOOD_WALK_04, FOOTSTEP_WOOD_WALK_05 };
const int SoundAtlas::NUM_FOOTSTEP_WOOD_WALK_SOUNDS =
	sizeof(SoundAtlas::FOOTSTEP_WOOD_WALK_SOUNDS) / sizeof(Sounds);

const SoundId SoundAtlas::GUN_PISTOL_SHOT_SOUNDS[] = {
	GUN_PISTOL_SHOT_01, GUN_PISTOL_SHOT_02, GUN_PISTOL_SHOT_03,
	GUN_PISTOL_SHOT_04, GUN_PISTOL_SHOT_05 };
const int SoundAtlas::NUM_GUN_PISTOL_SHOT_SOUNDS =
	sizeof(SoundAtlas::GUN_PISTOL_SHOT_SOUNDS) / sizeof(Sounds);

const SoundId SoundAtlas::GUN_PISTOL_SHOT_SILENCED_SOUNDS[] = {
	GUN_PISTOL_SHOT_SILENCED_01, GUN_PISTOL_SHOT_SILENCED_02,
	GUN_PISTOL_SHOT_SILENCED_03, GUN_PISTOL_SHOT_SILENCED_04,
	GUN_PISTOL_SHOT_SILENCED_05 };
const int SoundAtlas::NUM_GUN_PISTOL_SHOT_SILENCED_SOUNDS =
	sizeof(SoundAtlas::GUN_PISTOL_SHOT_SILENCED_SOUNDS) / sizeof(Sounds);

const SoundId SoundAtlas::GUN_RIFLE_SHOT_SOUNDS[] = {
	GUN_RIFLE_SHOT_01, GUN_RIFLE_SHOT_02, GUN_RIFLE_SHOT_03,
	GUN_RIFLE_SHOT_04 };
const int SoundAtlas::NUM_GUN_RIFLE_SHOT_SOUNDS =
	sizeof(SoundAtlas::GUN_RIFLE_SHOT_SOUNDS) / sizeof(Sounds);

const SoundId SoundAtlas::GUN_SHOTGUN_SAWED_OFF_SHOT_SOUNDS[] = {
	GUN_SHOTGUN_SAWED_OFF_SHOT_01, GUN_SHOTGUN_SAWED_OFF_SHOT_02,
	GUN_SHOTGUN_SAWED_OFF_SHOT_03, GUN_SHOTGUN_SAWED_OFF_SHOT_04 };
const int SoundAtlas::NUM_GUN_SHOTGUN_SAWED_OFF_SHOT_SOUNDS =
	sizeof(SoundAtlas::GUN_SHOTGUN_SAWED_OFF_SHOT_SOUNDS) / sizeof(Sounds);

const SoundId SoundAtlas::GUN_SHOTGUN_SHOT_SOUNDS[] = {
	GUN_SHOTGUN_SHOT_01, GUN_SHOTGUN_SHOT_02, GUN_SHOTGUN_SHOT_03,
	GUN_SHOTGUN_SHOT_04 };
const int SoundAtlas::NUM_GUN_SHOTGUN_SHOT_SOUNDS =
	sizeof(SoundAtlas::GUN_SHOTGUN_SHOT_SOUNDS) / sizeof(Sounds);

SoundAtlas::SoundAtlas()
{
	loadedSounds[NO_SOUND] = NULL;
	loadedSounds[FOOTSTEP_GRASS_RUN_01] = Mix_LoadWAV("../sounds/footstep_grass_run_01.wav");
	loadedSounds[FOOTSTEP_GRASS_RUN_02] = Mix_LoadWAV("../sounds/footstep_grass_run_02.wav");
	loadedSounds[FOOTSTEP_GRASS_RUN_03] = Mix_LoadWAV("../sounds/footstep_grass_run_03.wav");
	loadedSounds[FOOTSTEP_GRASS_RUN_04] = Mix_LoadWAV("../sounds/footstep_grass_run_04.wav");
	loadedSounds[FOOTSTEP_GRASS_RUN_05] = Mix_LoadWAV("../sounds/footstep_grass_run_05.wav");
	loadedSounds[FOOTSTEP_GRASS_WALK_01] = Mix_LoadWAV("../sounds/footstep_grass_walk_01.wav");
	loadedSounds[FOOTSTEP_GRASS_WALK_02] = Mix_LoadWAV("../sounds/footstep_grass_walk_02.wav");
	loadedSounds[FOOTSTEP_GRASS_WALK_03] = Mix_LoadWAV("../sounds/footstep_grass_walk_03.wav");
	loadedSounds[FOOTSTEP_GRASS_WALK_04] = Mix_LoadWAV("../sounds/footstep_grass_walk_04.wav");
	loadedSounds[FOOTSTEP_GRASS_WALK_05] = Mix_LoadWAV("../sounds/footstep_grass_walk_05.wav");
	loadedSounds[FOOTSTEP_GRAVEL_RUN_01] = Mix_LoadWAV("../sounds/footstep_gravel_run_01.wav");
	loadedSounds[FOOTSTEP_GRAVEL_RUN_02] = Mix_LoadWAV("../sounds/footstep_gravel_run_02.wav");
	loadedSounds[FOOTSTEP_GRAVEL_RUN_03] = Mix_LoadWAV("../sounds/footstep_gravel_run_03.wav");
	loadedSounds[FOOTSTEP_GRAVEL_RUN_04] = Mix_LoadWAV("../sounds/footstep_gravel_run_04.wav");
	loadedSounds[FOOTSTEP_GRAVEL_RUN_05] = Mix_LoadWAV("../sounds/footstep_gravel_run_05.wav");
	loadedSounds[FOOTSTEP_WOOD_WALK_01] = Mix_LoadWAV("../sounds/footstep_wood_walk_01.wav");
	loadedSounds[FOOTSTEP_WOOD_WALK_02] = Mix_LoadWAV("../sounds/footstep_wood_walk_02.wav");
	loadedSounds[FOOTSTEP_WOOD_WALK_03] = Mix_LoadWAV("../sounds/footstep_wood_walk_03.wav");
	loadedSounds[FOOTSTEP_WOOD_WALK_04] = Mix_LoadWAV("../sounds/footstep_wood_walk_04.wav");
	loadedSounds[FOOTSTEP_WOOD_WALK_05] = Mix_LoadWAV("../sounds/footstep_wood_walk_05.wav");
	loadedSounds[GUN_PISTOL_SHOT_01] = Mix_LoadWAV("../sounds/gun_pistol_shot_01.wav");
	loadedSounds[GUN_PISTOL_SHOT_02] = Mix_LoadWAV("../sounds/gun_pistol_shot_02.wav");
	loadedSounds[GUN_PISTOL_SHOT_03] = Mix_LoadWAV("../sounds/gun_pistol_shot_03.wav");
	loadedSounds[GUN_PISTOL_SHOT_04] = Mix_LoadWAV("../sounds/gun_pistol_shot_04.wav");
	loadedSounds[GUN_PISTOL_SHOT_05] = Mix_LoadWAV("../sounds/gun_pistol_shot_05.wav");
	loadedSounds[GUN_PISTOL_SHOT_SILENCED_01] = Mix_LoadWAV("../sounds/gun_pistol_shot_silenced_01.wav");
	loadedSounds[GUN_PISTOL_SHOT_SILENCED_02] = Mix_LoadWAV("../sounds/gun_pistol_shot_silenced_02.wav");
	loadedSounds[GUN_PISTOL_SHOT_SILENCED_03] = Mix_LoadWAV("../sounds/gun_pistol_shot_silenced_03.wav");
	loadedSounds[GUN_PISTOL_SHOT_SILENCED_04] = Mix_LoadWAV("../sounds/gun_pistol_shot_silenced_04.wav");
	loadedSounds[GUN_PISTOL_SHOT_SILENCED_05] = Mix_LoadWAV("../sounds/gun_pistol_shot_silenced_05.wav");
	loadedSounds[GUN_RIFLE_SHOT_01] = Mix_LoadWAV("../sounds/gun_rifle_shot_01.wav");
	loadedSounds[GUN_RIFLE_SHOT_02] = Mix_LoadWAV("../sounds/gun_rifle_shot_02.wav");
	loadedSounds[GUN_RIFLE_SHOT_03] = Mix_LoadWAV("../sounds/gun_rifle_shot_03.wav");
	loadedSounds[GUN_RIFLE_SHOT_04] = Mix_LoadWAV("../sounds/gun_rifle_shot_04.wav");
	loadedSounds[GUN_SHOTGUN_SAWED_OFF_SHOT_01] = Mix_LoadWAV("../sounds/gun_shotgun_sawed_off_shot_01.wav");
	loadedSounds[GUN_SHOTGUN_SAWED_OFF_SHOT_02] = Mix_LoadWAV("../sounds/gun_shotgun_sawed_off_shot_02.wav");
	loadedSounds[GUN_SHOTGUN_SAWED_OFF_SHOT_03] = Mix_LoadWAV("../sounds/gun_shotgun_sawed_off_shot_03.wav");
	loadedSounds[GUN_SHOTGUN_SAWED_OFF_SHOT_04] = Mix_LoadWAV("../sounds/gun_shotgun_sawed_off_shot_04.wav");
	loadedSounds[GUN_SHOTGUN_SHOT_01] = Mix_LoadWAV("../sounds/gun_shotgun_shot_01.wav");
	loadedSounds[GUN_SHOTGUN_SHOT_02] = Mix_LoadWAV("../sounds/gun_shotgun_shot_02.wav");
	loadedSounds[GUN_SHOTGUN_SHOT_03] = Mix_LoadWAV("../sounds/gun_shotgun_shot_03.wav");
	loadedSounds[GUN_SHOTGUN_SHOT_04] = Mix_LoadWAV("../sounds/gun_shotgun_shot_04.wav");

	//gLow = Mix_LoadWAV( "../sounds/low.wav" );

	//gMusic = Mix_LoadMUS( "music/beat.wav" );

}

Mix_Chunk* SoundAtlas::getSound(int soundId)
{
	return loadedSounds[soundId];
}

void SoundAtlas::playSound(int soundId)
{
	assert(soundId && soundId < NUM_SOUNDS);
	Mix_PlayChannel(-1, loadedSounds[soundId], 0);
}

SoundId getSoundByType(int soundType)
{
		switch (soundType)
		{
			case SoundType::NONE:
				return SoundId::NO_SOUND;
			case SoundType::FOOTSTEP_GRASS_RUN:
				return getFootstepGrassRunSound();
			case SoundType::FOOTSTEP_GRASS_WALK:
				return getFootstepGrassWalkSound();
			case SoundType::FOOTSTEP_WOOD_WALK:
				return getFootstepWoodWalkSound();
			case SoundType::PISTOL_SHOT:
				return getPistolShotSound();
			case SoundType::PISTOL_SHOT_SILENCED:
				return getPistolShotSilencedSound();
			case SoundType::RIFLE_SHOT:
				return getRifleShotSound();
			case SoundType::SHOTGUN_SAWED_OFF_SHOT:
				return getShotgunSawedOffShotSound();
			case SoundType::SHOTGUN_SHOT:
				return getShotgunShotSound();
			default:
				throw runtime_error("Invalid sound type");
		}
}

SoundId SoundAtlas::getFootstepGrassRunSound()
{
	return FOOTSTEP_GRASS_RUN_SOUNDS[rand() % static_cast<int>(NUM_FOOTSTEP_GRASS_RUN_SOUNDS + 1)];
}

SoundId SoundAtlas::getFootstepGrassWalkSound()
{
	return FOOTSTEP_GRASS_WALK_SOUNDS[rand() % static_cast<int>(NUM_FOOTSTEP_GRASS_WALK_SOUNDS + 1)];
}

SoundId SoundAtlas::getFootstepWoodWalkSound()
{
	return FOOTSTEP_WOOD_WALK_SOUNDS[rand() % static_cast<int>(NUM_FOOTSTEP_WOOD_WALK_SOUNDS + 1)];
}

SoundId SoundAtlas::getPistolShotSound()
{
	return GUN_PISTOL_SHOT_SOUNDS[rand() % static_cast<int>(NUM_GUN_PISTOL_SHOT_SOUNDS + 1)];
}

Sounds SoundAtlas::getPistolShotSilencedSound()
{
	return GUN_PISTOL_SHOT_SILENCED_SOUNDS[rand() % static_cast<int>(NUM_GUN_PISTOL_SHOT_SILENCED_SOUNDS + 1)];
}

SoundId SoundAtlas::getRifleShotSound()
{
	return GUN_RIFLE_SHOT_SOUNDS[rand() % static_cast<int>(NUM_GUN_RIFLE_SHOT_SOUNDS+ 1)];
}

SoundId SoundAtlas::getShotgunSawedOffShotSound()
{
	return GUN_SHOTGUN_SAWED_OFF_SHOT_SOUNDS[rand() % static_cast<int>(NUM_GUN_SHOTGUN_SAWED_OFF_SHOT_SOUNDS + 1)];
}

SoundId SoundAtlas::getShotgunShotSound()
{
	return GUN_SHOTGUN_SHOT_SOUNDS[rand() % static_cast<int>(NUM_GUN_SHOTGUN_SAWED_OFF_SHOT_SOUNDS + 1)]; // TODO: MIGHT NEED TO RENAME GUN_SHOTGUN_SHOT_SOUNDS
}

SoundAtlas::~SoundAtlas()
{
	for (int i = 1; i < NUM_SOUNDS; i++)
	{
		Mix_FreeChunk(loadedSounds[i]);
		loadedSounds[i] = NULL;
	}
}
