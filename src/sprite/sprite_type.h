#ifndef SPRITE_TYPE_H
#define SPRITE_TYPE_H

/*
Defines the types of sprites recognized by the Sprite class.
*/
enum class SpriteType
{
	NONE,
	CIVILIAN,
	PLAYER
};

namespace SpriteTypes
{
	const int NUM_TYPES = 3;
}

#endif
