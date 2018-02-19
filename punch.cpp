#include "punch.h"

Punch::Punch(SDL_Point handPos, int facingDir, Sprite* attacker) : Attack(getPos(handPos, facingDir), facingDir, attacker, NULL)
{
	damage = 5;
}

SDL_Rect Punch::getPos(SDL_Point handPos, int facingDir)
{
	switch (facingDir)
	{
		case DIRECTION_RIGHT:
			return SDL_Rect { handPos.x, handPos.y - PUNCH_WIDTH / 2, PUNCH_LENGTH, PUNCH_WIDTH };
			
		case DIRECTION_UP:
			return SDL_Rect { handPos.x - PUNCH_WIDTH / 2, handPos.y - PUNCH_LENGTH, PUNCH_WIDTH, PUNCH_LENGTH };
				
		case DIRECTION_DOWN:
			return SDL_Rect { handPos.x - PUNCH_WIDTH / 2, handPos.y, PUNCH_WIDTH, PUNCH_LENGTH };
			
		case DIRECTION_LEFT:
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