#ifndef KNOCKBACK_ACTION_H
#define KNOCKBACK_ACTION_H

#include "action.h"
#include "sprite.h"

// sprite is knocked in the given direction
class KnockbackAction : public Action 
{

	// direction of knockback
	int direction;
	// number of times apply has been called TODO: MILLISECONDS
	int numApplies = 0;
	
	public:
		KnockbackAction(int direction);
		void init(Sprite* sprite);
		bool apply(Sprite* sprite, int ms);
};

#endif