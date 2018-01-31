#include "action.h"

void Action::reset()
{
	elapsedTime = 0;
}

Action::~Action()
{
	printf("Deleting Action\n");	
}

HealthRegenAction::HealthRegenAction(int amount, int duration)
{
	amountPerMs = amount / duration;
	printf("Created HealthRegenAction\n");
}

bool HealthRegenAction::apply(Sprite* sprite, int ms)
{
	if (elapsedTime + ms > duration)
	{
		sprite->addHealth((duration - elapsedTime) * amountPerMs); // TODO: DOUBLE CHECK
	} 
	else 
	{
		sprite->addHealth(ms * amountPerMs);	
	}
	elapsedTime += ms;
	return elapsedTime < duration;
}

KnockbackAction::KnockbackAction(int direction)
{
	this->direction = direction;
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