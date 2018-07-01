#include "animation_sequence.h"

AnimationSequence::AnimationSequence(Spritesheet* right, Spritesheet* left, Spritesheet* up, Spritesheet* down)
{
	anims[DIRECTION::DIRECTION_UP] = up;
	anims[DIRECTION::DIRECTION_DOWN] = down;
	anims[DIRECTION::DIRECTION_RIGHT] = right;
	anims[DIRECTION::DIRECTION_LEFT] =	left;
}

bool AnimationSequence::hasDir(int dir)
{
	return anims[dir];
}

void AnimationSequence::printDebug()
{
	printf("AnimSequence With Spritesheets %d %d %d %d %d\n", anims[0], anims[1], anims[2], anims[3], anims[4]);
}
