#include "punch.h"

Punch::Punch(SDL_Point handPos, Direction facingDir, Sprite* attacker) : Attack(getPos(handPos, facingDir), attacker)
{
	damage = 5;
}

SDL_Rect Punch::getPos(SDL_Point handPos, Direction facingDir)
{
	switch (facingDir)
	{
		case Direction::RIGHT:
			return SDL_Rect { handPos.x, handPos.y - PUNCH_WIDTH / 2, PUNCH_LENGTH, PUNCH_WIDTH };

		case Direction::UP:
			return SDL_Rect { handPos.x - PUNCH_WIDTH / 2, handPos.y - PUNCH_LENGTH, PUNCH_WIDTH, PUNCH_LENGTH };

		case Direction::DOWN:
			return SDL_Rect { handPos.x - PUNCH_WIDTH / 2, handPos.y, PUNCH_WIDTH, PUNCH_LENGTH };

		case Direction::LEFT:
			return SDL_Rect { handPos.x - PUNCH_LENGTH, handPos.y - PUNCH_WIDTH / 2, PUNCH_LENGTH, PUNCH_WIDTH };

	}
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
