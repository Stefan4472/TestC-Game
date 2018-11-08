#include "game_utils.h"

float GameUtil::distSquared(Sprite* s1, Sprite* s2)
{
	return (s2->x - s1->x) * (s2->x - s1->x) + (s2->y - s1->y) * (s2->y - s1->y);
}

float GameUtil::distSquared(float x0, float y0, float x1, float y1)
{
	return (x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1);
}

float GameUtil::distSquared(Sprite* sprite, Sound* sound)
{
	return (sprite->x - sound->x) * (sprite->x - sound->x) + (sprite->y - sound->y)  * (sprite->y - sound->y);
}

SDL_Rect GameUtil::offsetRect(SDL_Rect rect, float offX, float offY)  // TODO: SHOULDN'T THIS ADD OFFX AND OFFY?
{  // TODO: NOTE, THIS LOSES PRECISION
	return SDL_Rect { (int) (rect.x - offX), (int) (rect.y - offY), rect.w, rect.h };
}
