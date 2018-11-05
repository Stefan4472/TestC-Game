#include "animation_sequence.h"

AnimationSequence::AnimationSequence(Spritesheet* right, Spritesheet* left, Spritesheet* up, Spritesheet* down)
{
	anims[DIRECTION::UP] = up;
	anims[DIRECTION::DOWN] = down;
	anims[DIRECTION::RIGHT] = right;
	anims[DIRECTION::LEFT] =	left;
}

bool AnimationSequence::hasDir(int dir)
{
	return anims[dir];
}

void AnimationSequence::printDebug()
{
	printf("AnimSequence With Spritesheets %lu %lu %lu %lu %d\n", anims[0], anims[1], anims[2], anims[3], anims[4]);
}
