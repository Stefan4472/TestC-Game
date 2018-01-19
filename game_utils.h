#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include <cmath>
#include "sprite.h"
#include "sound.h"

// returns square of Euclidean distance between given sprites
float distSquared(Sprite* s1, Sprite* s2);

// returns square of Euclidean distance between given coordinate pairs
float distSquared(float x0, float y0, float x1, float y1);

// returns square of Euclidean distance between given sprite and given sound
float distSquared(Sprite* sprite, Sound* sound);

#endif