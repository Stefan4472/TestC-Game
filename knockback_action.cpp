#include "knockback_action.h"

KnockbackAction::KnockbackAction(int direction)
{
	this->direction = direction;
}
	
void KnockbackAction::init(Sprite* sprite)
{
	switch (direction)
	{
		case DIRECTION_RIGHT:
			sprite->speedX = 4;
			break;

		case DIRECTION_LEFT:
			sprite->speedX = -4;
			break;

		case DIRECTION_UP:
			sprite->speedY = -4;
			break;

		case DIRECTION_DOWN:
			sprite->speedY = 4;
			break;
	}
}

bool KnockbackAction::apply(Sprite* sprite, int ms)
{
	numApplies++;
	// todo: apply over time and use method calls (don't just mess with coordinates)
	return numApplies < 3;
}