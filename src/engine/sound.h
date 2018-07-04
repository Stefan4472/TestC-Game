#ifndef SOUND_H
#define SOUND_H

#include "sound_atlas.h"

class Sprite;

// In-game representation of a sound. Has a soundId (mapping to an actual sound
// file in SoundAtlas), a coordinate position, a Sprite* that it was created by
// (can be NULL), and a range in which it can be "heard" (i.e. a radius).
class Sound
{
  public:
    // sound in SoundAtlas to play
    Sounds soundId;
    // coordinates of sound's center
    float x, y;
    // radius in which the sound can be heard from center
    int radius;
    // radius squared. makes distance calculations easier
    int radiusSquared;
    // reference to sprite that the sound originates from
    Sprite* creator = NULL;

    Sound(Sounds soundId, float x, float y, int radius, Sprite* creator);

};

#endif
