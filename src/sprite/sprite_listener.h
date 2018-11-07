#ifndef SPRITE_LISTENER_H
#define SPRITE_LISTENER_H

#include "direction.h"
#include "sprite_state.h"

/*
Provides an interface for Sprite callbacks. This is to be notified about Sprite
changes of state (e.g., for teh SpriteController).
*/
class SpriteListener
{
	public:
    // called when the sprite changes direction, starts/stops walking/running
    virtual void onMovementChanged(Direction dir, SpriteState moveState) = 0;
    // called when the sprite gains or loses health
		virtual void onHealthChanged(int amount, int newHealth) = 0;
};

#endif
