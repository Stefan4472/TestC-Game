#include "punch.h"

Punch::Punch(SDL_Rect position, int dir, Sprite* attacker) : Attack(position, dir, attacker, NULL)
{
	damage = 5;
}

void Punch::update(int ms)
{
	elapsedTime += ms;
	finished = (elapsedTime > MAX_DURATION);
}

void Punch::handleSpriteCollision()
{
	finished = true;
}

void Punch::handleObjectCollision()
{
	finished = true;
}