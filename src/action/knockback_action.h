#ifndef KNOCKBACK_ACTION_H
#define KNOCKBACK_ACTION_H

#include "sprite_action.h"
#include "sprite.h"
#include "direction.h"

// sprite is knocked in the given direction
class KnockbackAction : public SpriteAction
{

	// direction of knockback
	Direction direction;
	// number of times apply has been called TODO: MILLISECONDS
	int numApplies = 0;

	public:
		KnockbackAction(Direction direction);
		void init(Sprite* sprite);
		bool apply(Sprite* sprite, int ms);
};

#endif
