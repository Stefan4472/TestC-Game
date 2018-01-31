#ifndef HEALTH_REGEN_ACTION_H
#define HEALTH_REGEN_ACTION_H

#include "action.h"
#include "sprite.h"

// sprite regains health over a specified amount of time
class HealthRegenAction : public Action
{
	// amount of health to regen per ms (calculated in constructor)
	float amountPerMs;
	// time (ms) action lasts, and time it has been going
	int duration = 0, elapsedTime = 0;

	public:
		HealthRegenAction(int amount, int duration);
		void init(Sprite* sprite);
		bool apply(Sprite* sprite, int ms);
};

#endif