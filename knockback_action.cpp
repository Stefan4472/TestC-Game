#include "knockback_action.h"

KnockbackAction::KnockbackAction(int direction)
{
	this->direction = direction;
}
	
void KnockbackAction::init(Sprite* sprite)
{
	
}

bool KnockbackAction::apply(Sprite* sprite, int ms)
{
	numApplies++;
	// todo: apply over time and use method calls (don't just mess with coordinates)
	switch (direction)  
	{	
		case DIRECTION_RIGHT:
			sprite->x += 32;
			break;
			
		case DIRECTION_LEFT:
			sprite->x -= 32;
			break;
			
		case DIRECTION_UP:
			sprite->y -= 32;
			break;
			
		case DIRECTION_DOWN:
			sprite->y += 32;
			break;
	}
	return numApplies < 3;
}