#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include <SDL2/SDL.h>
#include <cmath>
#include "sprite.h"
#include "sound.h"

namespace GameUtil
{
  // returns square of Euclidean distance between given sprites
  float distSquared(Sprite* s1, Sprite* s2);

  // returns square of Euclidean distance between given coordinate pairs
  float distSquared(float x0, float y0, float x1, float y1);

  // returns square of Euclidean distance between given sprite and given sound
  float distSquared(Sprite* sprite, Sound* sound);

  // returns copy of rect with x -= offX and y -= offY TODO: THIS LOSES THE FLOAT PRECISION. BEWARE!!!
  SDL_Rect offsetRect(SDL_Rect rect, float offX, float offY);
}
#endif
