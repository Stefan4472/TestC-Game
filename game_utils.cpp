#include "game_utils.h"

float distSquared(Sprite* s1, Sprite* s2)
{
	return (s2->x - s1->x) * (s2->x - s1->x) + (s2->y - s1->y) * (s2->y - s1->y);
}