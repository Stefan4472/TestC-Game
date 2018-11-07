#ifndef SPRITE_STATE_H
#define SPRITE_STATE_H

/*
Defines the states a sprite can be in
*/
enum class SpriteState
{
	IDLING,
	WALKING,
	RUNNING,
	USING_ITEM,
  DYING
};

namespace SpriteStates
{
  final int NUM_STATES = 5;
}

#endif
