#ifndef SPRITE_BUFF_H
#define SPRITE_BUFF_H

#include <SDL2/SDL.h>
#include "sound_atlas.h"
#include "texture_atlas.h"
#include "sound.h"

class Sprite;

using namespace std;

class SpriteBuff
{
  public:
    // whether the buff can be deleted by the game engine
    bool destroy = false;
    // prepares the sprite to start receiving the buff
    virtual void init(Sprite* sprite) = 0;
    // applies the given buff to the Sprite over number of milliseconds.
    // returns false once the action is completed
    virtual bool apply(Sprite* sprite, int ms) = 0;
    // queries the SpriteBuff to add its sounds to the given vector and clear its
    // internal queue. The sounds added the vector will be played in the current
    // frame.
    virtual void getAndClearSounds(vector<Sound> sounds) = 0;
    // draw the buff over the sprite
    virtual void drawToSprite(SDL_Renderer* renderer, TextureAtlas* textureAtlas,
      Sprite* sprite) = 0;
};

#endif
