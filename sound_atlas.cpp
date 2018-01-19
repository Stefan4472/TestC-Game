#include "sound_atlas.h"

SoundAtlas::SoundAtlas()
{
	loadedSounds[NO_SOUND] = NULL;
	loadedSounds[SOUND_1] = Mix_LoadWAV( "sounds/scratch.wav" );
	loadedSounds[SOUND_2] = Mix_LoadWAV( "sounds/high.wav" );
	loadedSounds[SOUND_3] = Mix_LoadWAV( "sounds/medium.wav" );
	//gLow = Mix_LoadWAV( "sounds/low.wav" );
	
	//gMusic = Mix_LoadMUS( "music/beat.wav" );
	
}

Mix_Chunk* SoundAtlas::getSound(int soundId)
{
	return NULL;
}

SoundAtlas::~SoundAtlas()
{
	for (int i = 1; i < NUM_SOUNDS; i++) 
	{
		Mix_FreeChunk(loadedSounds[i]);
		loadedSounds[i] = NULL;
	}
	//delete[] loadedSounds;
	/*
	
	//The music that will be played
Mix_Music *gMusic = NULL;

//The sound effects that will be used
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;	*/
}