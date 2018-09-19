#ifndef SOUND_H
#define SOUND_H

#include "sound_ids.h"

class Sprite;

/*
In-game representation of a sound. Has a soundType (used to map it to a sound
file in SoundAtlas), a coordinate position, a Sprite* that it was created by
(can be NULL), and a range in which it can be "heard" (i.e. a radius).

The class is designed so that it can be created without access to a SoundAtlas
(which is why it does not take a SoundId or radius in the constructor).
*/
class Sound
{
  public:
    // soundType in SoundAtlas to play
    SoundType soundType;
    // coordinates of sound's center
    float x, y;
    // radius in which the sound can be heard from center
    int radius = 0;  // TODO: MAKE TILE-BASED?
    // radius squared. makes distance calculations easier
    int radiusSquared = 0;
    // reference to sprite that the sound originates from
    Sprite* creator = NULL;

    // constructor: radius can be set later by the game engine
    Sound(SoundType soundType, float x, float y, Sprite* creator);

};

#endif
