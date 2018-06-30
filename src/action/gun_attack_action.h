#ifndef GUN_ATTACK_ACTION_H
#define	GUN_ATTACK_ACTION_H

#include "sprite_action.h"
#include "follow_action.h"
#include "sprite.h"
#include "path_finder_interface.h"

// Sprite follows given target, attempting to shoot them (to death). Returns false when 
// sprite is out of bullets or has killed the target.

class GunAttackAction {

	// action for sprite to follow target
	FollowSpriteAction* followAction = NULL;
	// sprite to attack
	Sprite* target = NULL;
	// gun being used to attack
	Item* gun = NULL;
	public:
		FollowAction(PathFinder* pathFinder, Sprite* target);
};

#endif