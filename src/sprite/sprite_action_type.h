#ifndef SPRITE_ACTION_TYPE_H
#define SPRITE_ACTION_TYPE_H

/*
Defines actions a sprite can take. TODO: RENAME SPRITESTATE?
*/
enum class SpriteActionType
{
	IDLING,
	WALKING,
	RUNNING,
	USING_ITEM,
  DYING
};

#endif
