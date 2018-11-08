#include "knockback_action.h"

KnockbackAction::KnockbackAction(Direction direction)
{
	this->direction = direction;
}

void KnockbackAction::init(Sprite* sprite)
{
	switch (direction)
	{
		case Direction::RIGHT:
			sprite->speedX = 4;
			break;

		case Direction::LEFT:
			sprite->speedX = -4;
			break;

		case Direction::UP:
			sprite->speedY = -4;
			break;

		case Direction::DOWN:
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
