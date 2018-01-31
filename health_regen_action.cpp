#include "health_regen_action.h"

HealthRegenAction::HealthRegenAction(int amount, int duration)
{
	amountPerMs = amount / duration;
	printf("Created HealthRegenAction\n");
}

void HealthRegenAction::init(Sprite* sprite)
{
	return;	
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